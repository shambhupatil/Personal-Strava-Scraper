#include "awsRequests.h"
#include "misc.h"
#include "oAuthRequests.h"
#include <aws/core/Aws.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/UpdateItemRequest.h>
#include <ctime>


std::string getAndUpdateCreds(std::string &table_name, std::string &client_id) {
	
	//1. connect to dynamo db and get creds
	//2. if expires_at is in the future go to step 5
	//3. do a requestAccessToken() which will get the latest access_toke, refresh_token and expires_at.
	//4. finally update the creds at dynamodb
	//5. return creds in json format
	

	//1.
	Aws::SDKOptions options;
	Aws::InitAPI(options);
	Aws::Client::ClientConfiguration clientConfiguration;
	clientConfiguration.region = "us-east-2";
	Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfiguration);
	Aws::DynamoDB::Model::GetItemRequest request;

	request.SetTableName(table_name);
	request.AddKey("client_id", Aws::DynamoDB::Model::AttributeValue().SetS(client_id));

	const Aws::DynamoDB::Model::GetItemOutcome& outcome = dynamoClient.GetItem(request);

	const Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> items = outcome.GetResult().GetItem();

	if (!items.empty()) {
		for (const auto& i : items) {
			std::cout << i.first << " : " << i.second.GetS() << std::endl;
		}
	}
	else {
		std::cout << "No record with " << client_id << " found" << std::endl;
		std::cerr << "Failed to get item: " << outcome.GetError().GetMessage();
	}
	//2.

	
	int expires_at = std::stoi(std::string(items.at("expires_at").GetS().c_str()));
	std::time_t curr_time = std::time(nullptr);
	//std::cout << result;
	if (curr_time > expires_at) {

		json newCreds = requestAccessToken(client_id, items.at("client_secret").GetS(), items.at("refresh_token").GetS());

		Aws::DynamoDB::Model::UpdateItemRequest request;
		request.SetTableName("strava-creds");
		request.AddKey("client_id", Aws::DynamoDB::Model::AttributeValue().SetS(client_id));
		std::string new_expires_at = std::to_string(int(newCreds.at("expires_at")));
		std::string new_refresh_token = newCreds["refresh_token"];
		std::string new_access_token = newCreds["access_token"];


		

		request.SetUpdateExpression("SET #a = :value1, #b = :value2, #c = :value3");
		
		Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> expressionAttributeValues;
		expressionAttributeValues[":value1"] = Aws::DynamoDB::Model::AttributeValue().SetS(new_expires_at);
		expressionAttributeValues[":value2"] = Aws::DynamoDB::Model::AttributeValue().SetS(new_refresh_token);
		expressionAttributeValues[":value3"] = Aws::DynamoDB::Model::AttributeValue().SetS(new_access_token);
		
		request.SetExpressionAttributeNames({ {"#a","expires_at"},{"#b","refresh_token"},{"#c","access_token"} });
		request.SetExpressionAttributeValues(expressionAttributeValues);
		//int new_expires_at = newCreds["expires_at"];

		const Aws::DynamoDB::Model::UpdateItemOutcome& outcome = dynamoClient.UpdateItem(request);

		if (outcome.IsSuccess()) {
			std::cout << "Item updated successfully" << std::endl;
		}
		else {
			std::cout << "Error" << outcome.GetError().GetMessage() << std::endl;
		}

		return new_access_token;

	}
	return items.at("access_token").GetS();
}
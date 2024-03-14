#include <nlohmann/json.hpp>
#include <fstream> 
#include "oAuthRequests.h"
#include "awsRequests.h"
using json = nlohmann::json;


json getAndUpdateCreds() {
	std::ifstream ifs("C:/Users/shamb/OneDrive/Desktop/c++/Strava/access_keys.json");
	json aws_creds = json::parse(ifs);
	//1. connect to dynamo db and get creds
	//2. if expires_at is in the future go to step 5
	//3. do a requestAccessToken() which will get the latest access_toke, refresh_token and expires_at.
	//4. finally update the creds at dynamodb
	//5. return creds in json format
	
	
	return aws_creds;
}
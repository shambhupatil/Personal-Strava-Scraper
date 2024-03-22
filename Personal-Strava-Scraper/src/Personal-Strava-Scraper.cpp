#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "../include/oAuthRequests.h"
#include "../include/awsRequests.h"
#include <aws/core/Aws.h>
#include "../include/stravaRequests.h"
#include "../include/misc.h"
#include <map>


int main(int argc, char** argv) {

	Aws::String table_name = "strava-creds";
	Aws::String client_id = "123032";
	std::string access_token = getAndUpdateCreds(table_name, client_id);
	std::cout << access_token << std::endl;
	//json r  = getActivites(access_token, 5,convertDateToTimestamp(10,0,2024,true),convertDateToTimestamp(15,0,2024,true));
	//for (auto& a : r) {
	//	std::cout << a<< std::endl;
	//	std::cout << a.at("start_date_local") << std::endl;
	//}
	std::unordered_map<std::string, float> aggregate = getAggregateOfActivities(1, 0, 2024, 22, 2, 2024, "month", "run");

	auto it = aggregate.cbegin();
	while (it != aggregate.cend()) {
		std::cout << it->first << ": " << it->second << std::endl;
		it++;
	}

	return 0;
}
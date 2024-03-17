#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "oAuthRequests.h"
#include "awsRequests.h"
#include <aws/core/Aws.h>


int main(int argc, char** argv) {

	Aws::String table_name = "strava-creds";
	Aws::String client_id = "123032";
	std::string access_token = getAndUpdateCreds(table_name, client_id);
	
	int a = 0;
	std::cin >> a;
	return 0;
}
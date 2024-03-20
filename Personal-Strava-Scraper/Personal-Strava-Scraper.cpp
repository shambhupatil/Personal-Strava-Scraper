#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "oAuthRequests.h"
#include "awsRequests.h"
#include <aws/core/Aws.h>
#include "stravaRequests.h"


int main(int argc, char** argv) {

	Aws::String table_name = "strava-creds";
	Aws::String client_id = "123032";
	std::string access_token = getAndUpdateCreds(table_name, client_id);
	std::cout << access_token << std::endl;
	getActivites(access_token, 5);

	//cpr::Parameters parameters = {
	//	{"client_id","123032"},
	//	{"redirect_uri","http://localhost"},
	//	{"response_type","code"},
	//	{"approval_prompt","auto"},
	//	{"scope","read_all"}
	//};
	//cpr::Response r = cpr::Get(cpr::Url{ "https://www.strava.com/oauth/mobile/authorize" },
	//	parameters);
	//std::cout << "Status code: " << r.status_code << '\n';

	//std::cout << "Text: " << r.text << '\n';
	//std::cout << r.url << std::endl;
	int a = 0;
	std::cin >> a;
	return 0;
}
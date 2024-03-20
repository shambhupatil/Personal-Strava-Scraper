#include <iostream>
#include "stravaRequests.h"
#include <aws/core/Aws.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;


void getActivites(std::string access_token, int num_of_activities) {

	cpr::Parameters parameters = {
		{"before","1710827545"},
		{"after","1710222745"}
	};
	cpr::Response r = cpr::Get(cpr::Url{ "https://www.strava.com/api/v3/athlete/activities" },
		cpr::Bearer{ access_token },
		parameters);
	std::cout << "Status code: " << r.status_code << '\n';
	std::cout << "Text: " << r.text << '\n';
	return;
}

//http://localhost/exchange_token?state=&code=f1bbb21ba33955b979f68cb87448c432a8b2f4de&scope=read,activity:read_all
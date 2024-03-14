#include <cpr/cpr.h>
#include "oAuthRequests.h"
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


void requestAccessToken(std::string clientId, std::string clientSecret) {
	return;
}
std::string refreshAccessToken(std::string clientId, std::string clientSecret,std::string refresh_token) {
	cpr::Parameters parameters = {
		{"client_id",clientId},
		{"client_secret",clientSecret},
		{"grant_type","refresh_token"},
		{"refresh_token",refresh_token}
	};
	cpr::Response r = cpr::Post(cpr::Url{ "https://www.strava.com/api/v3/oauth/token" }, parameters);
	std::cout << "Status code: " << r.status_code << '\n';

	//std::cout << "Text: " << r.text << '\n';

	json jsonResponse = json::parse(r.text);
	return jsonResponse["access_token"];


}
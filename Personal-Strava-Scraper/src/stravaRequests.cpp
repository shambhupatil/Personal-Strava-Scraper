#include <iostream>
#include "../include/stravaRequests.h"
#include <aws/core/Aws.h>
#include <cpr/cpr.h>
#include "../include/misc.h"
#include "../include/awsRequests.h"
#include <map>

using json = nlohmann::json;


json getActivites(std::string access_token, int num_of_activities, int start_time, int end_time) {

	cpr::Parameters parameters = {
		{"after",std::to_string(start_time)},
		{"before",std::to_string(end_time)},
		{"per_page","200"},
		//{"page","3"}
	};
	cpr::Response r = cpr::Get(cpr::Url{ "https://www.strava.com/api/v3/athlete/activities" },
		cpr::Bearer{ access_token },
		parameters);
	//std::cout << "Status code: " << r.status_code << '\n';
	//std::cout << "Text: " << r.text << '\n';

	return json::parse(r.text);
}

std::unordered_map<std::string, float> getAggregateOfActivities(int start_date, int start_month, int start_year, int end_date, int end_month, int end_year,
	std::string period, std::string activityType) {
	int start_time = convertDateToTimestamp(start_date, start_month, start_year, true);
	int end_time = convertDateToTimestamp(end_date, end_month, end_year, true);
	std::string table_name = "strava-creds";
	std::string client_id = "123032";
	std::string access_token = getAndUpdateCreds(table_name, client_id);

	

	if (period == "day") {
		return getDayAggregate(getActivites(access_token, 10, start_time, end_time), activityType);
	}
	else if (period == "month") {
		return getMonthAggregate(getActivites(access_token, 10, start_time, end_time), activityType);
	}
	else
		return getYearAggregate(getActivites(access_token, 10, start_time, end_time), activityType);
}


std::unordered_map<std::string,float> getDayAggregate(json activities, std::string activityType){
	std::unordered_map<std::string, float> ans;
	for (auto& activity : activities) {
		std::string curr_date = activity["start_date_local"];
		if (ans.find(curr_date) == ans.end()) {
			ans[curr_date] = 0.0;
		}
		
		ans[curr_date] += float(activity["distance"]) / 1000;
	}
	return ans;
}

std::unordered_map<std::string, float> getMonthAggregate(json activities, std::string activityType) {
	std::unordered_map<std::string, float> ans;
	for (auto& activity : activities) {
		std::string curr_month = activity["start_date_local"];
		curr_month = curr_month.substr(0, 7);
		if (ans.find(curr_month) == ans.end()) {
			ans[curr_month] = 0.0;
		}

		ans[curr_month] += float(activity["distance"]) / 1000;
	}
	return ans;
}

std::unordered_map<std::string, float> getYearAggregate(json activities, std::string activityType) {
	std::unordered_map<std::string, float> ans;
	for (auto& activity : activities) {
		std::string curr_month = activity["start_date_local"];
		curr_month = curr_month.substr(0, 4);
		if (ans.find(curr_month) == ans.end()) {
			ans[curr_month] = 0.0;
		}

		ans[curr_month] += float(activity["distance"]) / 1000;
	}
	return ans;
}

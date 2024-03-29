//Header guard?
#include <vector>
#include <nlohmann/json.hpp>
#include <map>
using json = nlohmann::json;

json getActivites(std::string access_token, int num_of_activities, int start_time, int end_time);


std::unordered_map<std::string,float> getAggregateOfActivities(int start_date, int start_month, int start_year, int end_date, int end_month, int end_year, std::string period, std::string activityType);

std::unordered_map<std::string, float> getDayAggregate(json activities, std::string activityType);

std::unordered_map<std::string, float> getMonthAggregate(json activities, std::string activityType);

std::unordered_map<std::string, float> getYearAggregate(json activities, std::string activityType);
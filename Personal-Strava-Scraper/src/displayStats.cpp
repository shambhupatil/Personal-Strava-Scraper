#include "../include/displayStats.h"
#include "../include/stravaRequests.h"
#include <cpr/cpr.h>



void displayLapsOfDaysActivity(int day, int month, int year) {
	json activities = getActivitiesOfDay(day, month, year);

	for (auto& activity : activities) {
		long long int activity_id = activity["id"];
		
		json laps = getLapsOfActivity(activity_id);
		std::cout << activity_id << "\n";
		displayLapsDetails(laps);
	}
}


void displayLapsDetails(json laps) {
	std::cout << "Lap		Distance	Time\n";
	for (auto& lap : laps) {
		std::cout << lap["name"] <<"		" << lap["distance"] << "		" << lap["moving_time"] << "\n";
	}
}
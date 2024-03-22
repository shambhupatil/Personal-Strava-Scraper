#include "../include/misc.h"
#include <ctime>

json getAwsCreds(std::string file_name) {
	std::ifstream ifs(file_name);
	json aws_creds = json::parse(ifs);
	return aws_creds;
}

int convertDateToTimestamp(int date, int month, int year, bool local) {
	struct tm time { 0 };
	time.tm_mday = date;
	time.tm_mon = month;
	time.tm_year = year - 1900;

	return mktime(&time);
}

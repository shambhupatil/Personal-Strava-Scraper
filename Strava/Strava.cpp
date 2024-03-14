#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "oAuthRequests.h"
#include "awsRequests.h"

int main(int argc, char** argv) {

	//getCreds();
	std::string access_token=refreshAccessToken("123032", "b39728704a2e7d25fbca7160a28458076dd2c3d3", "a417d80539c313bef62d2aecbfe10fdb80ddd21f");
	

	//cpr::Response r = cpr::Get(cpr::Url{ "https://www.strava.com/api/v3/athlete" },
	//	cpr::Bearer{"b00a30f26b11501dcdac947b573a2ac41ee7bd19"});
	//std::cout << "Status code: " << r.status_code << '\n';
	//std::cout << "Header:\n";
	//for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
	//	std::cout << '\t' << kv.first << ':' << kv.second << '\n';
	//}
	//
	//std::cout << "Text: " << r.text << '\n';
	int a = 0;
	std::cin >> a;
	return 0;
}
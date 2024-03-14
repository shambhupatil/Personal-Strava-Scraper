#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "oAuthRequests.h"
#include "awsRequests.h"

int main(int argc, char** argv) {

	json creds = getAndUpdateCreds();
	//std::string access_token=requestAccessToken("123032", "b39728704a2e7d25fbca7160a28458076dd2c3d3", "a417d80539c313bef62d2aecbfe10fdb80ddd21f");
	

	
	int a = 0;
	std::cin >> a;
	return 0;
}
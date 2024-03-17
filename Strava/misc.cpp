#include "misc.h"

json getAwsCreds(std::string file_name) {
	std::ifstream ifs(file_name);
	json aws_creds = json::parse(ifs);
	return aws_creds;
}
//Header guard?

#include <nlohmann/json.hpp>
#include <fstream> 
#include <vector>
using json = nlohmann::json;

json getAwsCreds(std::string file_name);
int convertDateToTimestamp(int date, int month, int year, bool local);


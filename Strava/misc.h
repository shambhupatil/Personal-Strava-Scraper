//Header guard?

#include <nlohmann/json.hpp>
#include <fstream> 
using json = nlohmann::json;

json getAwsCreds(std::string file_name);


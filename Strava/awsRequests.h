//header guard??
#include <aws/core/Aws.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string getAndUpdateCreds(std::string& table_name, std::string& client_id);
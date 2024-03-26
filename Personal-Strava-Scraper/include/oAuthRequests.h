#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

json requestAccessToken(std::string clientId, std::string clientSecret, std::string refresh_token);
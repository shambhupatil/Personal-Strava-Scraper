#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
using json = nlohmann::json;

void displayLapsOfDaysActivity(int day, int month, int year, std::string access_token);

void displayLapsDetails(json laps);
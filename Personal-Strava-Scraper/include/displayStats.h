#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <map>
using json = nlohmann::json;

void displayLapsOfDaysActivity(int day, int month, int year);

void displayLapsDetails(json laps);
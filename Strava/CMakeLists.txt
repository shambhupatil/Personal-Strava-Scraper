# CMakeList.txt : CMake project for Strava, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(CMAKE_CXX_STANDARD 17)
add_executable (Strava "Strava.cpp" "Strava.h" "oAuthRequests.cpp" "oAuthRequests.h" "awsRequests.cpp" "awsRequests.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Strava PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(Strava PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(Strava PRIVATE cpr::cpr)
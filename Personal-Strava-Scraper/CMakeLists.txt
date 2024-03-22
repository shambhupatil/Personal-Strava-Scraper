# CMakeList.txt : CMake project for Personal-Strava-Scraper, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Personal-Strava-Scraper "src/Personal-Strava-Scraper.cpp" "include/Personal-Strava-Scraper.h" "src/oAuthRequests.cpp" "include/oAuthRequests.h" "src/awsRequests.cpp" "include/awsRequests.h" "src/misc.cpp" "include/misc.h" "src/stravaRequests.cpp" "include/stravaRequests.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Personal-Strava-Scraper PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}${BIN_SUB_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}${BIN_SUB_DIR})
endif()

# TODO: Add tests and install targets if needed.
include(FetchContent)


# CPR
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)


#Nlohmann JSON
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

#AWS

set(SERVICE_COMPONENTS s3 dynamodb)
set(WINDOWS_BUILD ${MSVC})

if (WINDOWS_BUILD) # Set the location where CMake can find the installed libraries for the AWS SDK.
    string(REPLACE ";" "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\cmake;" SYSTEM_MODULE_PATH "${CMAKE_SYSTEM_PREFIX_PATH}/aws-cpp-sdk-all")
    list(APPEND CMAKE_PREFIX_PATH ${SYSTEM_MODULE_PATH})
endif ()

list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\cmake\\AWSSDK")
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\")
list(APPEND CMAKE_PREFIX_PATH "C:\\Program Files (x86)\\aws-cpp-sdk-all\\lib\\cmake\\")
find_package(AWSSDK REQUIRED COMPONENTS ${SERVICE_COMPONENTS})

if (WINDOWS_BUILD)
    # Copy relevant AWS SDK for C++ libraries into the current binary directory for running and debugging.

    # set(BIN_SUB_DIR "/Debug") # if you are building from the command line you may need to uncomment this
    # and set the proper subdirectory to the executables' location.

    AWSSDK_CPY_DYN_LIBS(SERVICE_COMPONENTS "" ${CMAKE_CURRENT_BINARY_DIR}${BIN_SUB_DIR})
endif ()


target_link_libraries(Personal-Strava-Scraper PRIVATE ${AWSSDK_LINK_LIBRARIES})
target_link_libraries(Personal-Strava-Scraper PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(Personal-Strava-Scraper PRIVATE cpr::cpr)

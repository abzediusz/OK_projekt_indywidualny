cmake_minimum_required(VERSION 3.29)
project(OK_projekt_ind)

set(CMAKE_CXX_STANDARD 20)

add_executable(OK_projekt_ind main.cpp

)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(OK_projekt_ind nlohmann_json::nlohmann_json)
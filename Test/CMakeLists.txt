cmake_minimum_required(VERSION 3.27)
project(MapboxTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(MapboxTest main.cpp)
target_include_directories(MapboxTest PUBLIC include PRIVATE ../MapboxNavigation/include)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(MapboxTest PRIVATE cpr::cpr)
target_link_libraries(MapboxTest PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(MapboxTest PRIVATE MapboxNavigation)

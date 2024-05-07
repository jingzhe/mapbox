cmake_minimum_required(VERSION 3.27)
project(MapboxNavigation)

set(CMAKE_CXX_STANDARD 20)

add_library(MapboxNavigation SHARED
        cpp/HttpService.cpp
        include/HttpService.h
        include/Model.h
        include/Navigation.h
        cpp/NavigationImpl.cpp
        include/NavigationImpl.h
        cpp/JsonParser.cpp
        include/JsonParser.h
        cpp/RouteCalculator.cpp
        include/RouteCalculator.h
        cpp/RouteSimulation.cpp
        include/RouteSimulation.h
        cpp/GuidanceGenerator.cpp
        include/GuidanceGenerator.h)

target_include_directories(MapboxNavigation PUBLIC include PRIVATE include)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(MapboxNavigation PRIVATE cpr::cpr)
target_link_libraries(MapboxNavigation PRIVATE nlohmann_json::nlohmann_json)
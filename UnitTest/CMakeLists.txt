cmake_minimum_required(VERSION 3.27)
project(unit_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(MapboxTest PUBLIC include PRIVATE ../MapboxNavigation/include)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(
        unit_test
        JsonParserTest.cpp
        GuidanceGenTest.cpp
)
target_link_libraries(unit_test GTest::gtest_main)
target_link_libraries(unit_test nlohmann_json::nlohmann_json)
target_link_libraries(unit_test MapboxNavigation)

include(GoogleTest)
gtest_discover_tests(unit_test)
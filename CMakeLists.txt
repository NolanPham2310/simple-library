cmake_minimum_required(VERSION 3.5.1)
project(simple-library)

find_package(nlohmann_json REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)
find_package(GTest REQUIRED)

add_library(simple-library SHARED src/simple-library.cpp)
target_include_directories(simple-library PUBLIC include)
target_link_libraries(simple-library nlohmann_json::nlohmann_json nlohmann_json_schema_validator)

add_executable(simple-library-test tests/simple-library-test.cpp)
target_link_libraries(simple-library-test simple-library GTest::GTest GTest::Main)

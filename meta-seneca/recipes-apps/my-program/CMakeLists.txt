cmake_minimum_required(VERSION 3.10)
project(my-program)

find_package(simple-library REQUIRED)

add_executable(my-program main.cpp)
target_link_libraries(my-program simple-library)

cmake_minimum_required(VERSION 3.10)

project(main)

add_library(add add/src/add.cpp)
target_include_directories(add PUBLIC add/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE add)

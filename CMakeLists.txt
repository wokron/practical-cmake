cmake_minimum_required(VERSION 3.10)

project(main)

add_executable(main src/main.cpp src/add.cpp)
target_include_directories(main PRIVATE include)

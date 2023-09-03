cmake_minimum_required(VERSION 3.10)

project(subdirectory)

message("this is ${PROJECT_NAME}")

option(EXTERN_OPTION "" ON)
add_subdirectory(extern)

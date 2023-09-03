cmake_minimum_required(VERSION 3.10)

project(variable)

set(USER_VAR "default")

message("the value of USER_VAR is ${USER_VAR}")

message("the name of project is ${PROJECT_NAME}")

message("the whole project's dir is ${CMAKE_SOURCE_DIR}")

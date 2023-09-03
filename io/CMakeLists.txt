cmake_minimum_required(VERSION 3.10)

project(io)

option(OPTION_VAR "this is some option" OFF)

message("the value of OPTION_VAR is ${OPTION_VAR}")

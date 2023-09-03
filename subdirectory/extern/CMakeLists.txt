cmake_minimum_required(VERSION 3.8)

project(extern_module)

option(EXTERN_OPTION "this is option in extern" OFF)

message("this is ${PROJECT_NAME}")

if(EXTERN_OPTION)
    message("will do something")
else()
    message("will do other things")
endif()

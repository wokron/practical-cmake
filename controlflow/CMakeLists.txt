cmake_minimum_required(VERSION 3.10)

project(controlflow)

option(OPTION_VAR "this is option" ON)

if(OPTION_VAR)
    message("OPTION_VAR is on")
else()
    message("OPTION_VAR is off")
endif()

set(STR_VAR "123")

if(STR_VAR MATCHES "123")
    message("is 123!")
elseif(STR_VAR MATCHES "456")
    message("is 456")
else()
    message("is other :(")
endif()


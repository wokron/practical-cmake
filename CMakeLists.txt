cmake_minimum_required(VERSION 3.10)

project(main)

add_subdirectory(add)
add_subdirectory(fibo)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE add fibo)

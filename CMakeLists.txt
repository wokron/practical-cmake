cmake_minimum_required(VERSION 3.10)

project(main)

enable_testing()

add_subdirectory(add)
add_subdirectory(fibo)
add_subdirectory(test)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE add fibo)

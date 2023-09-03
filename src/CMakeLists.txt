cmake_minimum_required(VERSION 3.10)

project(main)

enable_testing()

add_subdirectory(add)
add_subdirectory(fibo)
add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE add fibo)

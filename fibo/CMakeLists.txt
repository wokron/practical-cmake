project(fibo)

add_library(${PROJECT_NAME} src/fibo.cpp)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} PRIVATE add)

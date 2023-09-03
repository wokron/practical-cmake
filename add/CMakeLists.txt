project(add)

add_library(${PROJECT_NAME} src/add.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

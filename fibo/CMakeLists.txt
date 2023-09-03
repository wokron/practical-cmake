add_library(fibo src/fibo.cpp)
target_include_directories(fibo INTERFACE include)
target_link_libraries(fibo PRIVATE add)

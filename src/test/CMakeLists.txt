add_executable(test_add test_add.cpp)
target_link_libraries(test_add add)

add_executable(test_fibo test_fibo.cpp)
target_link_libraries(test_fibo fibo)

add_test(NAME test_add COMMAND test_add)
add_test(NAME test_fibo COMMAND test_fibo)

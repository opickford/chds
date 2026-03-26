add_executable(test_vec 
    "test_vec.c"
)

target_link_libraries(test_vec PRIVATE chds)

add_test(NAME test_vec COMMAND test_vec)
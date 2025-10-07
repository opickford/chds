add_executable(tests 
    "main.c"
    
    "test_vec.h"
    "test_vec.c"
)

target_link_libraries(tests PRIVATE chds)

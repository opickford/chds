add_executable(tests 
    "main.c"
    
    "test_vector.h"
    "test_vector.c"
)

target_link_libraries(tests PRIVATE chds)

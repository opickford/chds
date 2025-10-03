cmake_minimum_required(VERSION 3.8)

project (chds VERSION 0.0.1 LANGUAGES C)

add_library(chds 
    INTERFACE
        # Add headers so they appear in Visual Studio
        "include/chds/vector.h"
)

add_library(chds::chds ALIAS chds)

target_include_directories(chds 
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

option(CHDS_BUILD_EXAMPLES "Build examples" ON)
option(CHDS_BUILD_TESTS "Build tests" ON)
option(CHDS_INSTALL "Enable installation" ON)

if (CHDS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (CHDS_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(CHDS_INSTALL)
    include(cmake/install.cmake)
endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "example")

cmake_minimum_required(VERSION 3.8)

project (chds VERSION 0.0.1 LANGUAGES C)

add_library(chds INTERFACE)

target_include_directories(chds INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add headers so they appear in Visual Studio
target_sources(chds INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/chds/vector.h
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

# Optional install support
#if(CHDS_INSTALL)
#    include(cmake/install.cmake)
#endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "example")

cmake_minimum_required(VERSION 3.31)

project (chds VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

configure_file(
	cmake/version.h.in
	${CMAKE_CURRENT_BINARY_DIR}/include/chds/version.h
)

add_library(chds 
    INTERFACE
        # Add headers so they appear in Visual Studio
        "include/chds/vec.h"
		"include/chds/chds.h"
)

add_library(chds::chds ALIAS chds)

target_include_directories(chds 
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

option(CHDS_BUILD_EXAMPLES "Build examples" ON)
option(CHDS_BUILD_TESTS "Build tests" ON)
option(CHDS_INSTALL "Enable installation" ON)

if (CHDS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (CHDS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(CHDS_INSTALL)
    include(cmake/install.cmake)
endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "example")

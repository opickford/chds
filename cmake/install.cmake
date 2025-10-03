# Export targets
install(TARGETS chds EXPORT chdsTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

install(EXPORT chdsTargets
    FILE chdsTargets.cmake
    NAMESPACE chds::
    DESTINATION lib/cmake/chds
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/chdsConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/chdsConfig.cmake"
    INSTALL_DESTINATION lib/cmake/chds
)

install(FILES
    "${CMAKE_BINARY_DIR}/chdsConfig.cmake"
    DESTINATION lib/cmake/chds
)
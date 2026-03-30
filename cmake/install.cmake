include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Register chds target for installation.
install(TARGETS chds
    EXPORT chdsTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Copy contents of include dir.
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# version.h lives in the build dir, so must be installed separately to the other headers.
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/chds/version.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/chds
)

# Generate and install chdsTargets.cmake.
install(EXPORT chdsTargets
    FILE chdsTargets.cmake
    NAMESPACE chds::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/chds
)

# Generate chdsConfig for find_package.
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/chdsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/chdsConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/chds"
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/chdsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/chdsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/chdsConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/chds
)
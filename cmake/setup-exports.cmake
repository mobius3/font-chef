include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Setup install of exported targets
install(EXPORT font-chef-targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/font-chef
)

# Macro to write config
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/font-chef-config-version.cmake"
  VERSION ${font-chef_VERSION}
  COMPATIBILITY SameMajorVersion
)

# Setup install of version config
install(
  FILES
    cmake/font-chef-config.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/font-chef-config-version.cmake"
  DESTINATION
   ${CMAKE_INSTALL_LIBDIR}/cmake/font-chef
  COMPONENT "Font Chef Development"
)

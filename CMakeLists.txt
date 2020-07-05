cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0063 NEW)
project(font-chef LANGUAGES C CXX VERSION 1.0.1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)

set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

option(FONT_CHEF_BUILD_DOCUMENTATION "Builds documentation using Doxygen" OFF)
option(FONT_CHEF_BUILD_EXAMPLES "Builds examples. Needs SDL2 already installed." OFF)

if (NOT APPLE)
  set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

add_subdirectory(third-party EXCLUDE_FROM_ALL)
add_subdirectory(src)

if (FONT_CHEF_BUILD_DOCUMENTATION)
  add_subdirectory(doc)
endif()

include(cmake/setup-exports.cmake)
include(cmake/font-chef-cpack.cmake)
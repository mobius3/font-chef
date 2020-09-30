include(GNUInstallDirs)
include(GenerateExportHeader)

set(I ../../include)
set(FONT_CHEF_PUBLIC_HEADERS
  ${I}/font-chef/character-mapping.h
  ${I}/font-chef/color.h
  ${I}/font-chef/font.h
  ${I}/font-chef/font-chef.h
  ${I}/font-chef/font-size.h
  ${I}/font-chef/rect.h
  ${I}/font-chef/size.h
  ${I}/font-chef/unicode-block.h
  ${CMAKE_CURRENT_BINARY_DIR}/font-chef/font-chef-export.h
)

add_library(font-chef
  color.c
  render-result.c
  font.c
  font-internal.c
  font-internal.h
  font-size.c
  rect.c
  unicode-block.c
  ${FONT_CHEF_PUBLIC_HEADERS}
)
add_library(font-chef++ INTERFACE)

get_target_property(STB_TT_LINK_LIBRARIES stb::truetype LINK_LIBRARIES)

target_link_libraries(font-chef PRIVATE $<TARGET_OBJECTS:stb::truetype>)
target_link_libraries(font-chef PRIVATE $<TARGET_OBJECTS:utf8-decode>)
target_link_libraries(font-chef PRIVATE ${STB_TT_LINK_LIBRARIES})

generate_export_header(font-chef BASE_NAME font-chef EXPORT_FILE_NAME font-chef/font-chef-export.h)

set_target_properties(font-chef PROPERTIES
  C_STANDARD 99
  VERSION ${font-chef_VERSION}
  SOVERSION ${font-chef_VERSION_MAJOR}
  PUBLIC_HEADER "${FONT_CHEF_PUBLIC_HEADERS}"
  OUTPUT_NAME "font-chef"
)

set(FONT_CHEF_PP_PUBLIC_HEADERS
  "${I}/font-chef/color.hpp"
  "${I}/font-chef/font.hpp"
  "${I}/font-chef/font-chef.hpp"
  "${I}/font-chef/font-size.hpp"
  "${I}/font-chef/render-result.hpp"
)

target_include_directories(font-chef
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    $<TARGET_PROPERTY:stb::truetype,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:utf8-decode,INTERFACE_INCLUDE_DIRECTORIES>
)

target_include_directories(font-chef++ INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<INSTALL_INTERFACE:include>
)

if (NOT CMAKE_BUILD_TYPE MATCHES "Release")
  target_compile_options(font-chef PRIVATE
    $<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -pedantic -fvisibility=hidden -Werror>
    $<$<C_COMPILER_ID:MSVC>:/W3 /WX /wd4820 /wd4668 /wd4204>
  )
endif()

target_compile_features(font-chef++
  INTERFACE
  cxx_auto_type
  cxx_variadic_templates
  cxx_lambdas
  cxx_nullptr
  cxx_right_angle_brackets
  cxx_static_assert
  cxx_template_template_parameters
)

target_link_libraries(font-chef++ INTERFACE font-chef)

install(TARGETS font-chef font-chef++
  EXPORT font-chef-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT "Font-Chef Runtime"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT "Font-Chef Runtime"
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT "Font-Chef Development"
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/font-chef
  COMPONENT "Font-Chef Development"
)

install(FILES "${FONT_CHEF_PP_PUBLIC_HEADERS}" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/font-chef)
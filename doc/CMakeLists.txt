# This cmake file creates and builds doxygen documentation. It also sets it in the install list.

find_package(Doxygen QUIET)
if (NOT FONT_CHEF_BUILD_DOCUMENTATION)
    return()
endif()

file(GLOB_RECURSE FONT_CHEF_PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../include/font-chef/*.h ${CMAKE_CURRENT_SOURCE_DIR}/../include/font-chef/*.hpp)

if(DOXYGEN_FOUND)
    set(DOXYGEN_TARGET_INDEX_HTML ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)
    set(CSS_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-extra.css)
    set(CSS_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen-extra.css)
    set(HEADER_HTML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/header.html)
    set(HEADER_HTML_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/header.html)
    set(LOGO_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/logo-blue.png)
    set(LOGO_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/logo-blue.png)
    set(MANUAL_DOX_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/manual.dox)
    set(MANUAL_DOX_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/manual.dox)
    set(DOXYGENLAYOUT_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/DoxygenLayout.xml)
    set(DOXYGENLAYOUT_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/DoxygenLayout.xml)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_command(OUTPUT
      ${CSS_OUTPUT}
      COMMAND ${CMAKE_COMMAND} -E copy ${CSS_INPUT} ${CSS_OUTPUT}
      DEPENDS ${CSS_INPUT}
    )
    add_custom_command(OUTPUT
      ${HEADER_HTML_OUTPUT}
      COMMAND ${CMAKE_COMMAND} -E copy ${HEADER_HTML_INPUT} ${HEADER_HTML_OUTPUT}
      DEPENDS ${HEADER_HTML_INPUT}
    )
    add_custom_command(OUTPUT
      ${LOGO_OUTPUT}
      COMMAND ${CMAKE_COMMAND} -E copy ${LOGO_INPUT} ${LOGO_OUTPUT}
      DEPENDS ${LOGO_INPUT}
    )
    add_custom_command(OUTPUT
      ${MANUAL_DOX_OUTPUT}
      COMMAND ${CMAKE_COMMAND} -E copy ${MANUAL_DOX_INPUT} ${MANUAL_DOX_OUTPUT}
      DEPENDS ${MANUAL_DOX_INPUT}
    )
    add_custom_command(OUTPUT
      ${DOXYGENLAYOUT_OUTPUT}
      COMMAND ${CMAKE_COMMAND} -E copy ${DOXYGENLAYOUT_INPUT} ${DOXYGENLAYOUT_OUTPUT}
      DEPENDS ${DOXYGENLAYOUT_INPUT}
    )
    add_custom_command(OUTPUT ${DOXYGEN_TARGET_INDEX_HTML}
      DEPENDS
        ${FONT_CHEF_PUBLIC_HEADERS}
        ${CSS_OUTPUT}
        ${MANUAL_DOX_OUTPUT}
        ${DOXYGENLAYOUT_OUTPUT}
        ${HEADER_HTML_OUTPUT}
        ${LOGO_OUTPUT}
      MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      COMMAND ${CMAKE_COMMAND} -E copy ${LOGO_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/html/
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
    add_custom_target(doc ALL DEPENDS ${DOXYGEN_TARGET_INDEX_HTML})

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc/font-chef)
else()
    message(STATUS "Doxygen was not found. Documentation will *NOT* be generated.")
endif(DOXYGEN_FOUND)

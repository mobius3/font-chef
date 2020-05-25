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

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_command(OUTPUT
      ${CSS_OUTPUT}
      COMMAND ${CMAKE_COMMAND} -E copy ${CSS_INPUT} ${CSS_OUTPUT}
      DEPENDS ${CSS_INPUT}
    )
    add_custom_command(OUTPUT ${DOXYGEN_TARGET_INDEX_HTML}
      DEPENDS ${FONT_CHEF_PUBLIC_HEADERS} ${CSS_OUTPUT}
      MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
    add_custom_target(doc ALL DEPENDS ${DOXYGEN_TARGET_INDEX_HTML})

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc/font-chef)
else()
    message(STATUS "Doxygen was not found. Documentation will *NOT* be generated.")
endif(DOXYGEN_FOUND)

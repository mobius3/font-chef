find_package(SDL2 QUIET)
if (SDL2_FOUND)
  add_subdirectory(c)
  add_subdirectory(cpp)
else()
  message(WARNING "SDL2 not found. Cannot build examples.")
endif()
project(stb-truetype)
add_library(stb-truetype OBJECT src/stb_truetype.c)

target_include_directories(stb-truetype PUBLIC include/)

if (NOT MSVC)
  target_link_libraries(stb-truetype PUBLIC "-lm")
endif()

add_library(stb::truetype ALIAS stb-truetype)
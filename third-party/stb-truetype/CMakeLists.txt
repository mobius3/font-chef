project(stb-truetype)
add_library(stb-truetype OBJECT src/stb_truetype.c)

target_include_directories(stb-truetype PUBLIC include/)
set_property(TARGET stb-truetype PROPERTY POSITION_INDEPENDENT_CODE ON)
add_library(stb::truetype ALIAS stb-truetype)
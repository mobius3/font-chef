project(utf8-decode)
add_library(utf8-decode OBJECT
  include/dfa.h
  src/dfa.c
  include/utf8-decode.h
  src/utf8-decode.c)

target_include_directories(utf8-decode PUBLIC include/)
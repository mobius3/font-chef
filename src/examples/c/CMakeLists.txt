add_executable(example-c main.c ../common/state.h ../common/state.c ../common/font.h ../common/font.c)
target_link_libraries(example-c SDL2 font-chef)
target_include_directories(example-c PRIVATE ../)

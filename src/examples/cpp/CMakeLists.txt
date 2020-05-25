add_executable(example-cpp main.cpp ../common/state.h ../common/state.hpp ../common/state.c ../common/font.h ../common/font.c)
target_link_libraries(example-cpp PRIVATE font-chef++ SDL2)
target_include_directories(example-cpp PRIVATE ../)
set_target_properties(example-cpp PROPERTIES LANGUAGE CXX)
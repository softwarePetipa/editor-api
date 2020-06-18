cmake_minimum_required (VERSION 3.14)
project (petitpa_lib LANGUAGES CXX VERSION 0.1)

file (GLOB_RECURSE LIB_SOURCES lib/*.cpp)

add_library (petipa_lib STATIC ${LIB_SOURCES})
target_include_directories (petipa_lib PRIVATE include)
target_compile_features (petipa_lib PUBLIC cxx_std_17)

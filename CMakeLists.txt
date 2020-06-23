cmake_minimum_required (VERSION 3.14)
project (petitpa_lib LANGUAGES CXX C VERSION 0.1)
set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

file (GLOB_RECURSE LIB_SOURCES lib/*.cpp imgui/*.cpp)

if (APPLE)
	add_compile_definitions(GL_SILENCE_DEPRECATION)
endif (APPLE)

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)

include(FetchContent)

FetchContent_Declare (soil2
	GIT_REPOSITORY https://github.com/SpartanJ/soil2
	GIT_TAG release-1.11)

FetchContent_MakeAvailable(soil2)

add_library(soil2
    ${soil2_SOURCE_DIR}/src/SOIL2/etc1_utils.c
    ${soil2_SOURCE_DIR}/src/SOIL2/image_DXT.c
    ${soil2_SOURCE_DIR}/src/SOIL2/image_helper.c
    ${soil2_SOURCE_DIR}/src/SOIL2/SOIL2.c)

target_include_directories(soil2 PUBLIC ${soil2_SOURCE_DIR}/src/SOIL2)

add_library (petipa_lib STATIC ${LIB_SOURCES})

target_include_directories (petipa_lib PRIVATE
	include
	${SDL2_INCLUDE_DIRS}
	${SDL2TTF_INCLUDE_DIR}
	${soil2_SOURCE_DIR}/src/SOIL2
)

target_link_libraries (petipa_lib ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY})

target_compile_features (petipa_lib PUBLIC cxx_std_17)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
	message (STATUS "${_variableName}=${${_variableName}}")
endforeach()

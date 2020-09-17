cmake_minimum_required (VERSION 3.4)
project (petitpa_lib LANGUAGES CXX C VERSION 0.1)
file (GLOB_RECURSE LIB_SOURCES lib/*.cpp imgui/*.cpp)
add_library (petipa_lib STATIC ${LIB_SOURCES})
target_compile_features (petipa_lib PUBLIC cxx_std_17)

include (FindPkgConfig)
pkg_check_modules (ALLEGRO allegro-5>=5.2.6
	allegro_font-5
	allegro_image-5
	allegro_memfile-5
	allegro_primitives-5)
if (${ALLEGRO_FOUND})
	message (STATUS "Allegro >= 5.2.6 found on the system.")
else()
	message (STATUS "Allegro >= 5.2.6 NOT found.  Fetching from repository.")
	include (FetchContent)
	set (WANT_DEMO OFF)
	set (WANT_TESTS OFF)
	set (WANT_EXAMPLES OFF)
	set (WANT_POPUP_EXAMPLES OFF)
	set (SHARED OFF)
	FetchContent_Declare (allegro
		GIT_REPOSITORY https://github.com/liballeg/allegro5
		GIT_TAG 5.2.6)
	FetchContent_MakeAvailable (allegro)
	set (ALLEGRO_INCLUDE_DIRS
		"${allegro_SOURCE_DIR}/include"
		"${allegro_BINARY_DIR}/include"
		"${allegro_SOURCE_DIR}/addons/font"
		"${allegro_SOURCE_DIR}/addons/image"
		"${allegro_SOURCE_DIR}/addons/memfile"
		"${allegro_SOURCE_DIR}/addons/primitives")
endif()

target_link_libraries (petipa_lib ${ALLEGRO_LIBRARIES})
target_include_directories (petipa_lib PRIVATE ${ALLEGRO_INCLUDE_DIRS})
target_link_directories (petipa_lib PRIVATE ${ALLEGRO_LIBRARY_DIRS})
target_link_options (petipa_lib PRIVATE -lallegro_main -lallegro_primitives)

target_include_directories (petipa_lib PRIVATE
	include
	${ALLEGRO_INCLUDE_DIRS}
)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
	message (STATUS "${_variableName}=${${_variableName}}")
endforeach()

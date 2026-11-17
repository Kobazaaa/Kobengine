cmake_minimum_required(VERSION 3.27)
project(Kobengine LANGUAGES CXX)

option(KOBENGINE_WARNINGS_AS_ERRORS "Treat warnings as errors in Kobengine" ON)

# Dependencies
if(NOT TARGET pompeii::pompeii)
	add_subdirectory(extern/pompeii)
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/FetchAndIncludeLibraries.cmake")

# Library
file(GLOB_RECURSE KOBENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(kobengine STATIC ${KOBENGINE_SOURCES})
add_library(kobengine::kobengine ALIAS kobengine)

target_compile_features(kobengine PUBLIC cxx_std_20)
set_target_properties(kobengine PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(kobengine
	PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(kobengine
	PUBLIC  pompeii::pompeii
	PRIVATE glfw
)

if(MSVC)
	set(KOBENGINE_WARNINGS /W4)
	if(KOBENGINE_WARNINGS_AS_ERRORS)
		list(APPEND KOBENGINE_WARNINGS /WX)
	endif()
else()
	set(KOBENGINE_WARNINGS -Wall -Wextra -Wpedantic)
	if(KOBENGINE_WARNINGS_AS_ERRORS)
		list(APPEND KOBENGINE_WARNINGS -Werror)
	endif()
endif()
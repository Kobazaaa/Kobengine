cmake_minimum_required(VERSION 3.27)

# Project Name
project(Kobengine)
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/engine/src")

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/engine")
add_subdirectory("${CMAKE_SOURCE_DIR}/renderer")

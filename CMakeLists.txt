# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(tempSens)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -lwiringPi -fdiagnostics-color")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/source")
include_directories("/usr/include")
link_directories("${PROJECT_SOURCE_DIR}/source")
link_directories("/usr/include/wiringPi")
add_executable(tempSens ${PROJECT_SOURCE_DIR}/source/senstest.cpp ${PROJECT_SOURCE_DIR}/source/tempSens.cpp) 

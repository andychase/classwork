cmake_minimum_required(VERSION 3.5)
project(assignment_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.cpp)
add_executable(assignment_3 ${SOURCE_FILES})
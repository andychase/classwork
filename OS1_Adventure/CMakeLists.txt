cmake_minimum_required(VERSION 3.2)
project(Project2Adventure)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES chasean.adventure.c)
add_executable(chasean.adventure ${SOURCE_FILES})

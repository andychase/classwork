cmake_minimum_required(VERSION 3.3)
project(problem1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lssl -lcrypto -std=c++11")
set(SOURCE_FILES main.cpp)
add_executable(problem1 ${SOURCE_FILES})
include_directories("/Users/a5c/Documents/openssl-1.0.2d/include")
target_link_libraries (problem1 "/Users/a5c/Documents/openssl-1.0.2d")

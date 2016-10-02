cmake_minimum_required(VERSION 3.5)
project(assignment_4)

set(CMAKE_CXX_COMPILER /usr/local/bin/clang++-3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fopenmp -stdlib=libc++ -std=c++11")
include_directories(/usr/local/include/ ~/Library/openmp/omp)
link_directories(/usr/local/lib/)

set(SOURCE_FILES main.cpp agents.cpp agents.h globals.h randf.h)
add_executable(assignment_4 ${SOURCE_FILES})

cmake_minimum_required(VERSION 3.5)
project(assignment_6)

set(CMAKE_CXX_COMPILER /usr/local/bin/clang++-3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenCL -fopenmp -stdlib=libc++ -std=c++11")
include_directories(/usr/local/include/ ~/Library/openmp/omp)
link_directories(/usr/local/lib/)

set(SOURCE_FILES first.cl first.cpp main.cpp)
add_executable(assignment_6 ${SOURCE_FILES})

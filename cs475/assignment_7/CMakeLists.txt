cmake_minimum_required(VERSION 3.5)
project(assignment_7)

set(CMAKE_CXX_COMPILER /usr/local/bin/clang++-3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenCL -framework GLUT -framework OpenGL -fopenmp -lglui -stdlib=libc++ -std=c++11")
include_directories(/usr/local/include/ ~/Library/openmp/omp /usr/local/Cellar/glui/2.36/include/GL/)
link_directories(/usr/local/lib/ /usr/local/Cellar/glui/2.36/lib)

set(SOURCE_FILES main.cpp)
add_executable(assignment_7 ${SOURCE_FILES})

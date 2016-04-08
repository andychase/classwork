cmake_minimum_required(VERSION 3.5)
project(assignment_1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
find_package(Threads)

set(SOURCE_FILES main.c)
add_executable(assignment_1 ${SOURCE_FILES})
target_link_libraries(assignment_1 ${CMAKE_THREAD_LIBS_INIT})

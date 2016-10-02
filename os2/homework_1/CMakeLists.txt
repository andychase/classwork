cmake_minimum_required(VERSION 2.4)
project(assignment_1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
find_package(Threads)

Try_Run(TEST_DRNG TEST_DRNG_COMPILE
        ${PROJECT_SOURCE_DIR}/vendor/test_drng_bin
        ${PROJECT_SOURCE_DIR}/vendor/test_drng/test.c
        )

if (TEST_DRNG AND (NOT (TEST_DRNG MATCHES FAILED_TO_RUN)))
    set(SOURCE_FILES main.c vendor/mt19937ar.c vendor/drng/cpuid.c vendor/drng/drng.c get_random.c)
    include_directories(vendor/using_drng)
else ()
    set(SOURCE_FILES main.c vendor/mt19937ar.c get_random.c)
    include_directories(vendor/not_using_drng)
endif ()
add_executable(assignment_1 ${SOURCE_FILES})
target_link_libraries(assignment_1 ${CMAKE_THREAD_LIBS_INIT})

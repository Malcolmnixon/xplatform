cmake_minimum_required (VERSION 2.6)

project (xplatform)

option(test "Build all tests." OFF)

include_directories("${PROJECT_SOURCE_DIR}/../../include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../bin/")

if (WIN32)
    add_library(
        xplatform STATIC
        ../../source/win32/critical_section.cpp
        ../../source/win32/mutex.cpp
        ../../source/win32/flags.cpp
        ../../source/win32/task.cpp
    )
else()
    add_library(
        xplatform STATIC
        ../../source/posix/critical_section.cpp
        ../../source/posix/mutex.cpp
        ../../source/posix/flags.cpp
        ../../source/posix/task.cpp
    )
endif()

if (test)
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll")
    add_subdirectory(../../extern/googletest extern/googletest)
    enable_testing()

    add_executable(
        test
        ../../test/os/test_critical_section.cpp
    )

    target_link_libraries(test gtest gtest_main xplatform)
    add_test(NAME test COMMAND test)
endif()


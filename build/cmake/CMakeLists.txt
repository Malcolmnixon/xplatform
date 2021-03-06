cmake_minimum_required (VERSION 2.6)

project (xplatform)

option(test "Build all tests." OFF)

include_directories("${PROJECT_SOURCE_DIR}/../../include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../bin/")

if (WIN32)
    add_library(
        xplatform STATIC
        ../../source/win32/os/critical_section.cpp
        ../../source/win32/os/mutex.cpp
        ../../source/win32/os/flags.cpp
        ../../source/win32/os/task.cpp
        ../../source/win32/os/time.cpp
    )
else()
    add_library(
        xplatform STATIC
        ../../source/posix/os/critical_section.cpp
        ../../source/posix/os/mutex.cpp
        ../../source/posix/os/flags.cpp
        ../../source/posix/os/task.cpp
        ../../source/posix/os/time.cpp
    )
endif()

if (test)
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll")
    add_subdirectory(../../extern/googletest extern/googletest)
    enable_testing()

    add_executable(
        test_runner
        ../../test/os/test_critical_section.cpp
        ../../test/os/test_flags.cpp
        ../../test/os/test_mutex.cpp
        ../../test/os/test_task.cpp
        ../../test/os/test_time.cpp
    )

    target_link_libraries(test_runner gtest gtest_main xplatform)
    add_test(NAME test_runner COMMAND test_runner)
endif()


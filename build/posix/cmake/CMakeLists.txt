cmake_minimum_required (VERSION 2.6)

project (xplatform)

include_directories("${PROJECT_SOURCE_DIR}/../../../include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../../bin/")

add_library(
    xplatform STATIC
    ../../../source/posix/critical_section.cpp
    ../../../source/posix/mutex.cpp
    ../../../source/posix/flags.cpp
    ../../../source/posix/task.cpp
)

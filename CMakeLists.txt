cmake_minimum_required(VERSION 3.22)
project(Particles)

set(PRODUCT $ENV{PRODUCT})
set(MAJOR $ENV{MAJOR})
set(MINOR $ENV{MINOR})
set(PATCH $ENV{PATCH})

set(COMPANY "Jerboa")
set(PRODUCT_NAME "${CMAKE_PROJECT_NAME}")
set(DESCRIPTION "${CMAKE_PROJECT_NAME} a skeleton project")
set(COPYRIGHT "Copyright (C) Jerboa - GPL v3")

string(TIMESTAMP TODAY "%Y-%m-%d:%H:%M:%S")
add_compile_definitions(TIMESTAMP="${TODAY}")
add_compile_definitions(PRODUCT=${PRODUCT})
add_compile_definitions(MAJOR=${MAJOR})
add_compile_definitions(MINOR=${MINOR})
add_compile_definitions(PATCH=${PATCH})

add_compile_definitions(COMPANY=${COMPANY})
add_compile_definitions(PRODUCT_NAME=${PRODUCT_NAME})
add_compile_definitions(DESCRIPTION=${DESCRIPTION})
add_compile_definitions(COPYRIGHT=${COPYRIGHT})

if (WINDOWS)
    add_subdirectory(common/windows/)
endif ()

list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS shader)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(RELEASE On)

set(CMAKE_CXX_STANDARD 17)
if (RELEASE)
    set(CMAKE_BUILD_TYPE Release)
else()
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (RELEASE)
    add_compile_definitions(BUILD_TYPE="Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-trapping-math -fno-rounding-math -fno-signaling-nans -fno-signed-zeros")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O3 -Wall")
else ()
    add_compile_definitions(BUILD_TYPE="Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -Wall -fsanitize=address")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

add_subdirectory(desktop)
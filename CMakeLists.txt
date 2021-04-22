# Project meta-data
cmake_minimum_required(VERSION 3.10)
project(proi_auto)

# Add a definition for debug builds
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_definitions(_DEBUG)
endif()

# Force C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable warnings and optimizations
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("MSVC Detected")
    set(CMAKE_CXX_FLAGS "/Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "/DEBUG /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
    message("Non-MSVC, trying GNU flags")
    set(CMAKE_CXX_FLAGS "-Wall -pthread")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()

# Ensure we link with SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add main code
add_executable(proi_auto main.cpp)
target_link_libraries(proi_auto ${SDL2_LIBRARIES})
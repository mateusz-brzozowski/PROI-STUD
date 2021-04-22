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
    set(CMAKE_CXX_FLAGS "-Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()

# ~~~ Locating SDL2 ~~~
# On Windows, SDL2_DIR env variable needs to contain the path of the extracted
# SDL2 development packages (https://www.libsdl.org/download-2.0.php).
# Additionally, this folder should have a file "sdl2-config.cmake" with following content:
# ```
# set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")
# # Support both 32 and 64 bit builds
# if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
#   set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib")
# else()
#   set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x86/SDL2main.lib")
# endif()
# string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
#```
# (source: https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/)
#
# On Linux, install an appropriate package and `pkg-find` will do all the work for us :^)
if(WIN32)
    find_package(SDL2 REQUIRED)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
endif()

# Add include dirs of the imported package
include_directories(${SDL2_INCLUDE_DIRS})

# Add main code
add_executable(proi_auto main.cpp)
target_link_libraries(proi_auto ${SDL2_LIBRARIES})

# Project meta-data
cmake_minimum_required(VERSION 3.10)
project(proi_auto)

# Project settings
set(SOURCES
    Car.cpp
    Map.cpp
    Window.cpp
)

set(FILES_TO_COPY
    images/car.bmp
)

# Add a definition for debug builds
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_definitions(_DEBUG)
endif()

# Force C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable warnings and optimizations
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("MSVC Detected, not changing any flags")
else()
    message("Non-MSVC, trying GNU flags")
    set(CMAKE_CXX_FLAGS "-Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()

# Include SDL2
# On Windows, dependencies should be handled by vcpkg; and you should integrate vcpkg with this CMake project
# On other systems we expect pkg-config to do the job for us.
if(WIN32)
    find_package(SDL2 CONFIG REQUIRED)
    set(SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2main)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

# Include images alongside the executable
foreach(FILE IN LISTS FILES_TO_COPY)
    configure_file("${FILE}" "${FILE}" COPYONLY)
endforeach()

# Add the library with game logic
add_library(proi_auto_logic ${SOURCES})

# Add main code
add_executable(proi_auto main.cpp)
target_link_libraries(proi_auto PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(proi_auto PRIVATE proi_auto_logic)

# Add tests
enable_testing()
add_subdirectory(tests)

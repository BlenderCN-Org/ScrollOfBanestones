cmake_minimum_required(VERSION 3.14)
project(ScrollsOfBanestones)

# Set the project name so that is can be more easilly accessed.
set(PROJECT_NAME ${CMAKE_PROJECT_NAME})

# Set the binary output into more standard directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)

# Ensure that the standard is actually enabled.
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Turn off any compiler specific extensions.
set(CMAKE_CXX_EXTENSIONS FALSE)

# Add the cmake modules directory
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include the source sub directory
add_subdirectory(Source)
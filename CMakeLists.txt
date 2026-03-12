cmake_minimum_required(VERSION 3.16)
project(chip8)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
# https://joshtronic.com/2024/01/14/cmake-compile-commands-json/ (for compile commands)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Add your source files
add_executable(chip8 src/chip8.cpp)

# Link SDL2 libraries
target_link_libraries(chip8 ${SDL2_LIBRARIES})

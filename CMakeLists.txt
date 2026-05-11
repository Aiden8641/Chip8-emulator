cmake_minimum_required(VERSION 3.16)
project(chip8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_executable(chip8)

target_sources(chip8 PRIVATE ./src/main.cpp ./src/chip8.cpp ./src/platform.cpp)

find_package(SDL3)

target_link_libraries(chip8 PRIVATE SDL3::SDL3)

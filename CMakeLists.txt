cmake_minimum_required(VERSION 3.13)  # CMake version check
project(MBAssembler)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)

add_executable(tester tester.cpp)
add_executable(Assembler assembler.cpp)
cmake_minimum_required(VERSION 3.0.0)
project(aer VERSION 0.1.0)

add_executable(aer src/main.cpp)
add_library(lib src/lib/TAObjects.cpp)

target_link_libraries(aer lib)

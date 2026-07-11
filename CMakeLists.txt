cmake_minimum_required(VERSION 4.1)
project(DSA_Project2)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(DSA-Project2
    ../DSA-Project2/Graph.cpp
    ../DSA-Project2/Graph.h
    ../DSA-Project2/main.cpp)
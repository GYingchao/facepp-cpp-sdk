cmake_minimum_required(VERSION 3.1)
project(libfacepp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES libfacepp.cpp)
add_executable(libfacepp ${SOURCE_FILES})
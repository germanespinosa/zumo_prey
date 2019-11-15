cmake_minimum_required(VERSION 3.3)

project(Zumo)

add_subdirectory(lib/libpixyusb2/)
include_directories(src)
#include(CMakeTests.txt)

add_executable( prey src/target.cpp )
target_include_directories( prey PUBLIC lib/libpixyusb2/include )
target_link_libraries(prey libpixy2)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

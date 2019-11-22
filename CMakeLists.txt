cmake_minimum_required(VERSION 3.3)

project(zumo_prey)

find_package(GComm CONFIG QUIET)

add_executable( zumo_prey src/prey.cpp include/joystick.h src/joystick.cpp)

target_include_directories(zumo_prey PRIVATE include)

target_link_libraries(zumo_prey PUBLIC gcomm)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
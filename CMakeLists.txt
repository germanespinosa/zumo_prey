cmake_minimum_required(VERSION 3.3)

project(Zumo)


include_directories(src)
include(CMakeFunctions.txt)

#add_program(target src/target.cpp src/uart.cpp )

#target_include_directories( target PUBLIC lib/pixy2/src/host/libpixyusb2/include )
#target_include_directories( target PUBLIC lib/pixy2/src/host/arduino/libraries/Pixy2 )

#add_library(libpixy2 STATIC IMPORTED)

#set_property(TARGET libpixy2 PROPERTY IMPORTED_LOCATION lib/pixy2/build/libpixyusb2/libpixy2.a)

#target_link_libraries(target libpixy2)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

#add_program(tty src/tty.cpp)

add_program(rx src/rx.cpp)
add_program(tx src/tx.cpp)

add_program(server src/server.cpp)
add_program(client src/client.cpp)



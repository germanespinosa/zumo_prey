cmake_minimum_required(VERSION 3.13)
project(libpixy2
        VERSION 2019.1.0
        DESCRIPTION "pixy2 c++ library"
        LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")


include_directories(src)
include_directories(include)

add_library ( libpixy2
        include/libpixyusb2.h
        include/usblink.h
        include/util.h
        src/libpixyusb2.cpp
        src/usblink.cpp
        src/util.cpp)

set_target_properties( libpixy2
        PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED On
        CXX_EXTENSIONS Off
        VERSION ${PROJECT_VERSION}
        RUNTIME_OUTPUT_DIRECTORY "bin/")


find_package(Libusb1 REQUIRED)

message(${LIBUSB1_INCLUDE_DIR})
target_include_directories( libpixy2 PRIVATE ${LIBUSB1_INCLUDE_DIR} )
message(${LIBUSB1_LIBRARY})

target_link_libraries( libpixy2 ${LIBUSB1_LIBRARY})

if(MSVC)
    target_compile_options(libpixy2 PRIVATE /W4)
else(MSVC)
    target_compile_options(libpixy2 PRIVATE -Wall -Wextra -pedantic)
endif(MSVC)

target_include_directories(libpixy2
        PRIVATE
        include )

target_compile_definitions(libpixy2 PRIVATE
        -DGE211_RESOURCES="$<JOIN:${GE211_RESOURCE_PATH},\"$<COMMA>\">")

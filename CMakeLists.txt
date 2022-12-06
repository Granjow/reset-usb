cmake_minimum_required(VERSION 3.7)
project(reset-usb)

set(CMAKE_CXX_STANDARD 17)

add_executable(reset-usb main.cpp)

install(TARGETS reset-usb RUNTIME DESTINATION bin)

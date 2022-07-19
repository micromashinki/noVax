cmake_minimum_required(VERSION 3.20)
project(noVax)

set(CMAKE_CXX_STANDARD 20)

add_executable(noVax Cflags.h Cmemory.hpp hex_printing.h noVAX.cpp ini-parser-master/ini.cpp ini-parser-master/ini.h)
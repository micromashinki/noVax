cmake_minimum_required(VERSION 3.10)
project(noVAX)

set(CMAKE_CXX_STANDARD 20)

if(DEFINED my_variable)
    add_library(noVAXLib STATIC ini-parser-master/ini.h ini-parser-master/ini.cpp)
    target_include_directories(noVAXLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
else()
    add_executable(noVAX noVAX.cpp ini-parser-master/ini.h ini-parser-master/ini.cpp)
    target_include_directories(noVAX PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

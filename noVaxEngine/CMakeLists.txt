cmake_minimum_required(VERSION 3.10)
project(noVAX-lib)

set(CMAKE_CXX_STANDARD 20)

add_library(noVAX-lib STATIC ini-parser-master/ini.h ini-parser-master/ini.cpp)
target_include_directories(noVAX-lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )

if(WIN32)
    target_link_libraries(noVAX-lib ws2_32)
endif ()

if(DEFINED ENV{googletest_ROOT_DIR})
    set(GTEST_ROOT $ENV{googletest_ROOT_DIR})
endif()

message(STATUS "GTEST_ROOT: ${GTEST_ROOT}")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(runTests tests/test.cpp)
target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES} pthread noVAX-lib)
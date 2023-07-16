cmake_minimum_required(VERSION 3.11)
project(noVAX-lib)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "*.hpp")
add_library(noVAX-lib ${SOURCES} Cprocessor.cpp tests/Cprocessor_addressing_8.cpp tests/Cprocessor_addressing_9.cpp)

# specify .hpp as source files
set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE CXX)

target_include_directories(noVAX-lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

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

add_executable(runTests tests/test.cpp tests/Cprocessor_save_load.cpp tests/Cprocessor_addressing_5.cpp tests/Cprocessor_operations_test.cpp tests/Cpocessor_vax_labs_tests.cpp tests/Cprocessor_addressing_6.cpp tests/Cprocessor_addressing_7.cpp tests/Cprocessor_addressing_8.cpp tests/Cprocessor_addressing_9.cpp tests/test.h)
target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES} pthread noVAX-lib)

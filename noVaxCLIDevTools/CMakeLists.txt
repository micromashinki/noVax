cmake_minimum_required(VERSION 3.10)
project(noVAX-cli)

set(CMAKE_CXX_STANDARD 20)

add_executable(noVAX-cli noVAX.cpp)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../noVaxEngine")
set(BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../noVaxEngine_binary")

add_subdirectory(${SOURCE_DIR} ${BINARY_DIR})

target_link_libraries(noVAX-cli PRIVATE noVAX-lib)
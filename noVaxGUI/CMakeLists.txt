cmake_minimum_required(VERSION 3.10)
project(noVax-gui)

set(CMAKE_CXX_STANDARD 11)

add_executable(noVax-gui
        item_colours.h
        panel_mem.h
        panel_msg.h
        panel_regs.h
        panels.h
        start.h
        panel_srch.cpp
        start.cpp
        panel_mem.cpp
        panel_msg.cpp
        panel_regs.cpp
        )


set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../noVaxEngine")
set(BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../noVaxEngine_binary")

add_subdirectory(${SOURCE_DIR} ${BINARY_DIR})


if(WIN32)
    find_package(OpenGL REQUIRED)
endif()

if(DEFINED ENV{wxWidgets_ROOT_DIR})
    set(wxWidgets_CONFIG_EXECUTABLE $ENV{wxWidgets_ROOT_DIR}/bin/wx-config)
endif()


find_package(wxWidgets REQUIRED COMPONENTS net core base)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
endif()

target_link_libraries(noVax-gui PRIVATE noVAX-lib ${wxWidgets_LIBRARIES})



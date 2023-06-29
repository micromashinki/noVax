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
add_subdirectory(noVaxEngine)

if(WIN32)
    find_package(OpenGL REQUIRED)
endif()

find_package(wxWidgets REQUIRED COMPONENTS net core base)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
endif()

target_link_libraries(noVax-gui PRIVATE noVAXLib ${wxWidgets_LIBRARIES})



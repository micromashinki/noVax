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

find_package(OpenGL)
find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(noVax-gui PRIVATE noVAXLib wx::core wx::base wx::gl)



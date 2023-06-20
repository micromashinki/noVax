cmake_minimum_required(VERSION 3.10)
project(noVax-gui)

set(CMAKE_CXX_STANDARD 14)

if(DEFINED ENV{wxWidgets_ROOT_DIR})
    set(wxWidgets_CONFIG_EXECUTABLE $ENV{wxWidgets_ROOT_DIR}/bin/wx-config)
endif()

set(AS_LIB "true")
find_package(wxWidgets REQUIRED COMPONENTS net core base)

if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
endif()

add_executable(noVax-gui
        item_colours.h
        panel_mem.h
        panel_msg.h
        panel_regs.h
        panel_srch.cpp
        start.cpp
        panel_mem.cpp
        panel_msg.cpp
        panel_regs.cpp
        panels.h
        start.h
        )
add_subdirectory(noVaxEngine)

target_link_libraries(noVax-gui PRIVATE noVAXLib ${wxWidgets_LIBRARIES})


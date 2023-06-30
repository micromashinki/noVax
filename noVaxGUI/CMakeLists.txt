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

if(WIN32)
    find_package(wxWidgets CONFIG REQUIRED)
elseif(UNIX)
    find_package(wxWidgets REQUIRED COMPONENTS net core base)
endif()

if(wxWidgets_FOUND AND UNIX)
    include(${wxWidgets_USE_FILE})
endif()

if(WIN32)
    target_link_libraries(noVax-gui PRIVATE noVAX-lib wx::core wx::base wx::gl)
elseif(UNIX)
    target_link_libraries(noVax-gui PRIVATE noVAX-lib ${wxWidgets_LIBRARIES})
endif()


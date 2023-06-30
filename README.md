# novax-gui-cmake

## Prerequisites
Before proceeding, make sure you have installed the following packages:
- git
- sudo privileges (if not root)
- GTK+ 3

## 

    sudo apt update
    sudo apt install -y git libgtk-3-dev

Install the wxWidgets
    
    git clone https://github.com/wxWidgets/wxWidgets.git --depth 1
    cd wxWidgets
    mkdir build-gtk
    cd build-gtk
    git submodule update --init --recursive
    ../configure
    make
    or set count core
    make -j <count core>
    sudo make install

Install the gtest

    git clone https://github.com/google/googletest.git  --depth 1
    cd googletest
    mkdir build
    cd build
    cmake .. 
    make
    sudo make install

##
Windows Installation

1) Установить clion
2) Установить vcpkg
3) Соеденить clion и vcpkg
4) Установить chocolatey
5) В консоли choco install mingw
6) Зайти в настройки PATH и подвинуть путь до mingw на самый верх
7) В консоли vcpkg install wxwidgets:x64-mingw-dynamic
8) В clion поменять компилятор на mingw установленный через choco
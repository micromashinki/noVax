# novax-gui-cmake

## Prerequisites
Before proceeding, make sure you have installed the following packages:
- git
- sudo privileges (if not root)
- GTK+ 3

## 

    sudo apt update
    sudo apt install -y git libgtk-3-dev

    # Clone wxWidgets repository
    git clone https://github.com/wxWidgets/wxWidgets.git --depth 1
    
    # Navigate into the wxWidgets directory
    cd wxWidgets
    
    # Create a new directory and navigate into it
    mkdir build-gtk
    cd build-gtk
    
    # Update git submodules
    git submodule update --init --recursive
    
    # Run the configure script with the desired install prefix
    ../configure
    
    # Compile the project
    make
    
    or set count core 

    make -j <count core>
    
    # Install the project
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
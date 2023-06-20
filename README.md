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

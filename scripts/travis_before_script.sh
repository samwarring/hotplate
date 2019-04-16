#!/bin/bash
set -x
set -e

# Create build directory
mkdir build
cd build

# If compiling for x86 linux, set up the cross-compilation environment
uname -a | grep Linux >/dev/null
export IS_LINUX=$?
if [ $IS_LINUX = 0 ] && [ $ARCH = x86 ]; then
    echo Setting up cross compilation for x86 linux from x64 linux...
    sudo dpkg --add-architecture i386
    sudo apt update
    sudo apt install -y g++-multilib libboost-all-dev:i386
    cmake .. -DCMAKE_BUILD_TYPE=$CONFIG -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain_x86_linux_on_x64_linux.cmake
elif [ $IS_LINUX = 0 ] && [ $ARCH = x64 ]; then
    echo Setting up native x64 Linux compilation environment...
    sudo apt update
    sudo apt install -y libboost-all-dev
    cmake .. -DCMAKE_BUILD_TYPE=$CONFIG
else
    echo Setting up native x64 Mac compilation environment...
    cmake .. -DCMAKE_BUILD_TYPE=$CONFIG
fi


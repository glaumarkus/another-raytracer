#!/bin/bash

EXT_DIRECTORY="external"
EIGEN_RELEASE="https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz"
GTEST_RELEASE="https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz"
SDL_RELEASE="https://github.com/libsdl-org/SDL/releases/download/release-2.30.0/SDL2-2.30.0.tar.gz"
IMGUI_RELEASE="https://github.com/ocornut/imgui/archive/refs/tags/v1.90.3.tar.gz"
CPP23_GCC="https://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-13.2.0/gcc-13.2.0.tar.gz"

echo "Starting install"

if [[ ! -d ${EXT_DIRECTORY} ]]; then
    mkdir -p "${EXT_DIRECTORY}"
fi
cd ${EXT_DIRECTORY}

# install eigen
wget "${EIGEN_RELEASE}"
tar -xvf ${EIGEN_RELEASE##*/}
rm ${EIGEN_RELEASE##*/}

# install gtest
wget "${GTEST_RELEASE}"
tar -xvf ${GTEST_RELEASE##*/}
rm ${GTEST_RELEASE##*/}

# install sdl
wget "${SDL_RELEASE}"
tar -xvf ${SDL_RELEASE##*/}
rm ${SDL_RELEASE##*/}

# install imgui
wget "${IMGUI_RELEASE}"
tar -xvf ${IMGUI_RELEASE##*/}
rm ${IMGUI_RELEASE##*/}

sudo apt-get install libglfw3 libglfw3-dev -y
sudo apt-get install libyaml-cpp-dev -y

# ./configure --enable-languages=c,c++ --disable-multilib
# make -j4
# sudo make install

cd .. 
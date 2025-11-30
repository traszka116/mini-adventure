#!/bin/bash
set -e
cd ./libs/SDL 
mkdir build
cmake -B build -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDL_TESTS=OFF
cmake --build build --config Release
cd ../../
mkdir dest
mkdir dest/bin
mv ./libs/SDL/build/libSDL3.so* ./dest/bin
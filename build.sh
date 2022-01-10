#!/bin/sh

# dependencies
sudo apt-get install libcgal-dev

# build
rm -r build
mkdir build && cd build
cmake ..
make 
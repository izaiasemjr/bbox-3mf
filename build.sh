#!/bin/sh

# dependencies


# build
rm -r build
mkdir build && cd build
cmake ..
make 
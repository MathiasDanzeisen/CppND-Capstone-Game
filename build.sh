#!/bin/bash -v

# Get dependencies and build
rm -r build
mkdir -p build
cd build
cmake .. -G "Unix Makefiles"

cmake --build .
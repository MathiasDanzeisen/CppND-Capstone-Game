#!/bin/bash -v

# Get dependencies and build
rm -r build
mkdir -p build
cd build
export CONAN_SYSREQUIRES_MODE=enabled
conan install -pr:b=default -pr:h=default -s build_type=Debug ..
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

cmake --build .
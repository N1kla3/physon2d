#!/bin/bash

rm -rf build && mkdir build && cmake -G Ninja -DPHYSON_EXAMPLES=ON -DPHYSON_TESTS=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B ./build -S .
cmake --build ./build -j 10 && cp build/compile_commands.json .

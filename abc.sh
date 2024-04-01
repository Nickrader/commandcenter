#!/bin/bash

# Cache dependencies directory
mv build/_deps/ .

# Delete build directory
rm -rf build/

# Remake build directory, so can replaced cached 
mkdir build/

# Replace cached
mv _deps/ build/_deps/

# Remove civetweb-subbuild; the patch doesn't play nice
rm -rf build/_deps/civetweb-subbuild/

# Configure CMake
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build projcet
cmake --build build -j $(nproc)

# Run the bot, using the BotConfig at project root.
./build/bin/CommandCenter

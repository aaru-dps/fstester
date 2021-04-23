#!/bin/bash
# Generates compilation databases for OpenWatcom
mkdir -p ../projects/compdb/ow/os2v2
cmake -B ../projects/compdb/ow/os2v2 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=toolchains/ow-os2.cmake ..

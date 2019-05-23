#!/usr/bin/env bash

rm -fr build
mkdir build
cd build
cmake ..
make clean
make -j4

#!/bin/bash

rm -rf build && mkdir build && cd build && cmake .. && make

./imgDisplay ../resources/img.jpg &
./vidDisplay ../resources/ &
wait
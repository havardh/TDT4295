#!/bin/bash
cd ../../libs/cpputest/
./configure
make
make check
cp *.a lib

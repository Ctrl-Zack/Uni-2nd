#!/bin/bash

rm -rf film && rm recap.txt
cp -r "film copy 3" ./film
gcc trabowo-c.c -o output/trabowo-c
./output/trabowo-c
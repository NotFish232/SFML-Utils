#!/bin/bash

set -e 

rm -f ./bin/*

for file in ./src/*; do
    g++ -c "$file" -o "./bin/$(basename $file .cpp).o"
done


ar crf "./lib/libsfml-utils.a" ./bin/*.o
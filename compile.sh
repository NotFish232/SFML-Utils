#!/bin/bash

set -e 

rm -f ./bin/*

for file in ./src/*; do
    g++ -c "$file" -o "./bin/$(basename $file .cpp).o"
done


ar crf "./lib/libsfml-utils.a" ./bin/*.o

sudo cp -r include /usr/include/sfml-utils
sudo cp lib/libsfml-utils.a /usr/lib/x86_64-linux-gnu/

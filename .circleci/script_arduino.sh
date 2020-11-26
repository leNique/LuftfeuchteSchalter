#!/usr/bin/env bash

mkdir $PWD/src/libraries
cp $PWD/lib $PWD/src/libraries
arduino-cli compile --output temp.bin -b arduino:avr:uno $PWD/src/main.cpp --debug



##arduino --verify --board arduino:avr:uno $PWD/src/main.cpp

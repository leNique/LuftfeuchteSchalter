#!/usr/bin/env bash

mkdir $PWD/src/libraries
cp -r $PWD/lib/* $PWD/src/libraries
arduino-cli compile --output temp.bin -b arduino:avr:uno $PWD/src/main.cpp --debug



arduino-cli config dump
dir $PWD/src/libraries
printf $PWD

##arduino --verify --board arduino:avr:uno $PWD/src/main.cpp

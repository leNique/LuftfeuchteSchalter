#!/usr/bin/env bash

arduino-cli compile --directories.data $PWD/lib --output temp.bin -b arduino:avr:uno $PWD/src/main.cpp --debug



##arduino --verify --board arduino:avr:uno $PWD/src/main.cpp

#!/usr/bin/env bash

arduino-cli compile --output temp.bin -b arduino:avr:uno $PWD/src/main.cpp --debug



##arduino --verify --board arduino:avr:uno $PWD/src/main.cpp

#!/usr/bin/env bash


cp -r $PWD/lib/* /home/circleci/Arduino/libraries


arduino-cli compile --output temp.bin -b arduino:avr:uno $PWD/src/main.cpp --debug

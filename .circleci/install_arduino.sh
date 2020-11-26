#!/usr/bin/env bash

sudo apt-get install bzip2
yes | sudo apt install python-pip
pip install pyserial
pip install --upgrade pip

wget -O arduino-cli-linux64.tar.bz2 https://github.com/arduino/arduino-cli/releases/download/0.3.3-alpha.preview/arduino-cli-0.3.3-alpha.preview-linux64.tar.bz2
bunzip2 arduino-cli-linux64.tar.bz2
tar xvf arduino-cli-linux64.tar

sudo mv arduino-cli-0.3.3-alpha.preview-linux64 /usr/local/share/arduino-cli
sudo ln -s /usr/local/share/arduino-cli /usr/local/bin/arduino-cli

##printf "board_manager:
##  additional_urls:
##    - https://dl.espressif.com/dl/package_esp32_index.json" >> .cli-config.yml
printf "directories:
data:  
- ./lib" >> .cli-config.yml
sudo mv .cli-config.yml /usr/local/share/

arduino-cli core update-index
##arduino-cli core update-index --directories.data $PWD/lib
##arduino-cli core install esp32:esp32
arduino-cli core install arduino:avr
arduino-cli lib install "SoftwareWire" "TM1637" "AM232X"






##wget http://downloads.arduino.cc/arduino-1.8.8-linux64.tar.xz
##tar xf arduino-1.8.8-linux64.tar.xz
##sudo mv arduino-1.8.8 /usr/local/share/arduino
##sudo ln -s /usr/local/share/arduino/arduino /usr/local/bin/arduino


##arduino lib install "TM1637" "AM232X"

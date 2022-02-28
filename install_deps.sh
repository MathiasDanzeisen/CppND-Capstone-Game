#!/bin/bash -v

# install prerequistits
sudo apt update
sudo apt install python3-pip -y
sudo apt install g++ -y
sudo apt install make -y
sudo apt install cmake -y
sudo apt install pkg-config -y

pip install conan

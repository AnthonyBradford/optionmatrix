#!/bin/bash

# A. Bradford

# Testing building OptionMatrix with and without QuantLib

# run command "$ script" prior to running this bash script
# when the bash script is done type Control-d
# Analyse with
# grep -E -i 'warning| Status:' typescript

# QuantLib does not exist as an apt-get installable package
# Do the following on actual QuantLib autotools package
# On my machine I have QuantLib located in ~/src/c++/QuantLib-1.36/
# Your location will differ
# The next line will uninstall QuantLib
(cd ~/src/c++/QuantLib-1.36/ && sudo make uninstall)

# Build optionmatrix without QuantLib
make clean; ./configure CXX=g++ ; make
make check
./src/gtk/optionmatrix --list
echo "[1] Status: Built with g++"
echo "[1] Status: Built without QuantLib"
echo

# QuantLib requires Boost
sudo apt-get install libboost-all-dev

# QuantLib does not exist as an apt-get installable package
# Do the following on actual QuantLib autotools package
# On my machine I have QuantLib located in ~/src/c++/QuantLib-1.36/
# Your location will differ
# The next line will install QuantLib
(cd ~/src/c++/QuantLib-1.36/ && make && sudo make install)

# Build optionmatrix with QuantLib
make clean; ./configure CXX=g++ ; make
make check
./src/gtk/optionmatrix --list
echo "[2] Status: Built with g++/QuantLib"
echo "[2] Status: QuantLib addes 29 more option models"
echo

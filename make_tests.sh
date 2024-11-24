#!/bin/bash

# A. Bradford

# doc/Makefile.am has optionmatrix.pdf and optionmatrix.info in EXTRA_DIST
# Texinfo should not be a required package for "make optionmatrix"
# Don't run make distclean it deletes optionmatrix.pdf in the
# distribution. make distclean does not delete optionmatrix.info
#make distclean

# We should be able to build optionmatrix without the following libraries
sudo apt-get remove libnewmat10-dev
sudo apt-get remove libitpp-dev
sudo apt-get remove libboost-all-dev

# QuantLib does not exist as a apt-get un-installable package.
# Do the following on actual QuantLib autotools package
# cd QuantLib; sudo make uninstall

# optionmatrix.info and optionmatrix.pdf require texinfo to be built, but
# they do not have to be build since they are included in the distribution
# see EXTRA_DIST in doc/Makefile.am
sudo apt-get remove texinfo

./configure
make
./src/gtk/optionmatrix --list
echo The number of option models should be less since we removed libraries
read -n 1 -s -r -p "[1] Press any key to continue"
echo

# We should be able to build optionmatrix with the following libraries and
# texinfo. The inclusion of libnewmat10-dev, libitpp-dev and
# libboost-all-dev add 3 more models.
sudo apt-get install libnewmat10-dev
sudo apt-get install libitpp-dev
sudo apt-get install libboost-all-dev
sudo apt-get install texinfo

# QuantLib does not exist as a apt-get installable package.
# Do the following on actual QuantLib autotools package
# cd QuantLib; sudo make ; sudo make install

./configure
make
./src/gtk/optionmatrix --list
echo The number of option models should be more since we added libraries
read -n 1 -s -r -p "[2] Press any key to continue"
echo

# Check for compiler warnings/errors with clang
make clean; ./configure CXX=clang++ ; make
make check
./src/gtk/optionmatrix --list
echo Built with clang
read -n 1 -s -r -p "[3] Press any key to continue"
echo

# Check for compiler warnings/errors with g++
make clean ./configure CXX=g++ ; make
make check
./src/gtk/optionmatrix --list
echo Built again with g++
read -n 1 -s -r -p "[4] Press any key to continue"
echo

# Remove GTK+ 3 and compile with GTK+ 2 (apt-get for Ubuntu)
sudo apt-get remove libgtk-3-dev
sudo apt-get install libgtk2.0-dev
make clean; ./configure ; make
make check
echo Built with GTK+ 2
read -n 1 -s -r -p "[5] Press any key to continue"

# Reinstall GTK+ 3 (apt-get for Ubuntu)
sudo apt-get install libgtk-3-dev
make clean; ./configure ; make
make check
echo Built with GTK+ 3
read -n 1 -s -r -p "[6] Press any key to continue"

sudo make install
# The following should yield installed optionmatrix files
find /usr -name "*optionmatrix*" -print 2>/dev/null
echo These are the installed optionmatrix files
read -n 1 -s -r -p "[7] Press any key to continue"

sudo make uninstall
find /usr -name "*optionmatrix*" -print 2>/dev/null
echo optionmatrix uninstalled. No optionmatrix files should be found in /usr
read -n 1 -s -r -p "[8] Press any key to continue"

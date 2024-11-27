#!/bin/bash

# A. Bradford

# run command "$ script" prior to running this bash script
# when the bash script is done type Control-d
# Analyse with
# egrep -i 'warning| Status:' typescript

# doc/Makefile.am has optionmatrix.pdf and optionmatrix.info in EXTRA_DIST
# Texinfo should not be a required package for "make optionmatrix"
# Don't run make distclean it deletes optionmatrix.pdf in the
# distribution. make distclean does not delete optionmatrix.info

# We should be able to build optionmatrix without the following libraries
sudo apt-get remove libnewmat10-dev
sudo apt-get remove libitpp-dev
sudo apt-get remove libboost-all-dev

# Need GTK+3 and curses
sudo apt-get install libgtk-3-dev libncurses-dev

# QuantLib does not exist as a apt-get un-installable package.
# Do the following on actual QuantLib autotools package
# cd QuantLib; sudo make uninstall

# optionmatrix.info and optionmatrix.pdf require texinfo to be built, but
# they do not have to be build since they are included in the distribution
# see EXTRA_DIST in doc/Makefile.am
sudo apt-get remove texinfo

make clean; ./configure CXX=g++; make
make check
./src/gtk/optionmatrix --list
# 167 option model count does not include models named like "Testing Option"  or "Testing Future"
echo "[1] Status: The number of option models should be 167 since we removed libraries"
echo "[1] Status: Built with g++/GTK+3"
echo "[1] Status: Built without libnewmat10-dev libitpp-dev libboost-all-dev texinfo"
echo "[1] Status: The build should *not* have dependency on texinfo"
echo

# We should be able to build optionmatrix with the following libraries and
# The inclusion of libnewmat10-dev, libitpp-dev and libboost-all-dev add
# 3 more models.
sudo apt-get install libnewmat10-dev
sudo apt-get install libitpp-dev
sudo apt-get install libboost-all-dev
sudo apt-get install texinfo

make clean; ./configure CXX=g++; make
make check
./src/gtk/optionmatrix --list
# 170 option model count does not include models named like "Testing Option"  or "Testing Future"
echo "[2] Status: The number of option models should be 170 more since we added libraries"
echo "[2] Status: Built with g++/GTK+3 libnewmat10-dev libitpp-dev libboost-all-dev texinfo"
echo

# Build with clang++
make clean; ./configure CXX=clang++ ; make
make check
./src/gtk/optionmatrix --list
echo "[3] Status: Built with clang/GTK+3"
echo

# Remove GTK+3 and build with GTK+ 2 (apt-get for Ubuntu)
sudo apt-get remove libgtk-3-dev
sudo apt-get install libgtk2.0-dev

make clean; ./configure CXX=g++; make
make check
echo "[5] Status: Built with g++/GTK+2"

# Build with clang++
make clean; ./configure CXX=clang++ ; make
make check
./src/gtk/optionmatrix --list
echo "[6] Status: Built with clang/GTK+2"
echo

# Reinstall GTK+3 (apt-get for Ubuntu)
sudo apt-get install libgtk-3-dev

make clean; ./configure CXX=g++; make
make check
echo "[7] Status: Built with g++/GTK+3"

sudo make install
echo "[8] Status: These are the installed optionmatrix files"
# The following should yield installed optionmatrix files
find /usr -name "*optionmatrix*" -print 2>/dev/null

sudo make uninstall
# The following should yield *no* files since we uninstalled optionmatrix
find /usr -name "*optionmatrix*" -print 2>/dev/null
echo "[9] Status: optionmatrix uninstalled. No optionmatrix files should be found in /usr"

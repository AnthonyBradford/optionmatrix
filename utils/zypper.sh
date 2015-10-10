#!/bin/sh

# Copyright (C) 2012 Anthony Bradford.

echo
echo Install proper packages for openSUSE/SUSE Linux Enterprise distributions
echo

sudo zypper install gcc-c++ llvm-clang ncurses-devel gtk2-devel gtk3-devel gsl gsl-devel help2man texinfo

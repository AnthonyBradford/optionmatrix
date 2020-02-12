#!/bin/sh

# Copyright (C) 2012 Anthony Bradford.

echo
echo Install proper packages for GNU/Linux distributions using the zypper package manager
echo

sudo zypper install gcc-c++ clang ncurses-devel gtk2-devel gtk3-devel gsl gsl-devel help2man texinfo automake

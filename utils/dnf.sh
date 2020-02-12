#!/bin/sh

# Copyright (C) 2012 Anthony Bradford.

echo
echo Install proper packages for GNU/Linux distributions using the dnf package manager
echo

dnf install gcc-c++ clang ncurses-devel gtk2-devel gtk3-devel gsl gsl-devel help2man boost-devel texinfo texlive texinfo-tex make

#!/bin/sh

# Copyright (C) 2012 Anthony Bradford.
# Check source code for TABs

grep -P '	' ../src/gtk/*.h ../src/gtk/*.cpp
grep -P '	' ../src/curses/*.h ../src/curses/*.cpp
grep -P '	' ../src/common/abradford/*.h ../src/common/abradford/*.cpp

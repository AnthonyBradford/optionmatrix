#!/bin/sh

# Copyright (C) 2012 Anthony Bradford.
# Check source code for TABs.
# In emacs run untabify to remove TABs.

grep -P '	' ../src/gtk/*.h ../src/gtk/*.cpp
grep -P '	' ../src/curses/*.h ../src/curses/*.cpp
grep -P '	' ../src/common/*.h ../src/common/*.cpp
grep -P '	' ../src/models/abradford/*.h ../src/models/abradford/*.cpp
grep -P '	' ../src/models/spinsky/*.h ../src/models/spinsky/*.cpp

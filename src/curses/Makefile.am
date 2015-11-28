bin_PROGRAMS = optionmatrix_console

optionmatrix_console_SOURCES = \
curses_calendar.cpp\
curses_demo.cpp\
curses_display.cpp\
curses_include.h\
curses_inputs.cpp\
curses_main.cpp\
curses_process.cpp\
curses_prop.cpp\
curses_misc.cpp

optionmatrix_console_CPPFLAGS = -I$(top_srcdir)/src/models/financialrecipes/src -I$(top_srcdir)/src/models/metaoptions/src -I$(top_srcdir)/src/common

optionmatrix_console_LDADD = ../common/liboptionmatrix.a ../models/abradford/libabradford.a ../models/spinsky/libspinsky.a ../models/financialrecipes/src/librecipes.a ../models/metaoptions/src/libmetaoptions.a

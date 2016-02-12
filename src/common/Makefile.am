AUTOMAKE_OPTIONS = subdir-objects
noinst_LIBRARIES = liboptionmatrix.a
noinst_HEADERS =  main.h extern.h

noinst_PROGRAMS = checks
TESTS = checks
check_PROGRAMS= $(TESTS)

checks_SOURCES = \
checks.cpp

liboptionmatrix_a_SOURCES = \
args.cpp\
cumulative_norm.cpp\
defaults.cpp\
defs.h\
distributions.cpp\
extern.h\
futures.cpp\
greeks.cpp\
license.h\
logger.cpp\
main.h\
metaoptions.h\
finrecipes.h\
misc.h\
test.h\
options_calls.cpp\
options_puts.cpp\
prototypes.h\
sanity.cpp\
termstructure.cpp\
time.cpp\
tickers.cpp\
QuantLib.h\
environment.h

liboptionmatrix_a_CFLAGS=$(FM) -O3 -std=c99 \
	-Werror -Wshadow -W -Wall -pedantic -DNDEBUG -Wmissing-prototypes

liboptionmatrix_a_CPPFLAGS = -I$(top_srcdir)/src/abradford -I$(top_srcdir)/src/financialrecipes/src -I$(top_srcdir)/src/metaoptions/src -I/.
liboptionmatrix_a_LIBADD = ../models/abradford/libabradford.a ../models/spinsky/libspinsky.a ../models/financialrecipes/src/librecipes.a ../models/metaoptions/src/libmetaoptions.a

checks_CPPFLAGS = -I$(top_srcdir)/src/models/abradford -I$(top_srcdir)/src/models/spinsky -I$(top_srcdir)/src/models/financialrecipes/src -I$(top_srcdir)/src/models/metaoptions/src -I$(top_srcdir)/src/common
checks_LDADD = ./liboptionmatrix.a ../models/abradford/libabradford.a ../models/spinsky/libspinsky.a  ../models/financialrecipes/src/librecipes.a ../models/metaoptions/src/libmetaoptions.a

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
options_calls.cpp\
options_puts.cpp\
prototypes.h\
sanity.cpp\
termstructure.cpp\
time.cpp\
tickers.cpp\
QuantLib.h\
abradford/basicmodels.h\
abradford/black_76.cpp\
abradford/black_scholes.cpp\
abradford/delta.cpp\
abradford/future.cpp\
abradford/merton_73.cpp\
abradford/pre-BSM.cpp\
spinsky/binomial.cpp\
spinsky/binomial.h

liboptionmatrix_a_CFLAGS=$(FM) -O3 -std=c99 \
	-Werror -Wshadow -W -Wall -pedantic -DNDEBUG -Wmissing-prototypes

liboptionmatrix_a_CPPFLAGS = -I$(top_srcdir)/src/financialrecipes/src -I$(top_srcdir)/src/metaoptions/src -I/.
liboptionmatrix_a_LIBADD = ../models/financialrecipes/src/librecipes.a ../models/metaoptions/src/libmetaoptions.a

checks_CPPFLAGS = -I$(top_srcdir)/src/models/financialrecipes/src -I$(top_srcdir)/src/models/metaoptions/src -I$(top_srcdir)/src/common
checks_LDADD = ./liboptionmatrix.a ../models/financialrecipes/src/librecipes.a ../models/metaoptions/src/libmetaoptions.a /usr/local/lib/libQuantLib.a

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([OptionMatrix],[1.4.4],[anthony_bradford@yahoo.com],[optionmatrix],[https://sourceforge.net/projects/optionmatrix/])
AM_INIT_AUTOMAKE([1.9 tar-ustar subdir-objects])
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/gtk/gtk_scale.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_RANLIB
# Variable MAKEINFO is defined automatically, use MAKEINFO_INSTALLED...
AC_PATH_PROG([MAKEINFO_INSTALLED], makeinfo)
AC_PATH_PROG([TEXI2ANY], texi2any)
AC_PATH_PROG([DBTOEPUB], dbtoepub)
AC_PATH_PROG([DBLATEX], dblatex)
AC_PATH_PROG([ASPELL], aspell)
AC_PATH_PROG([DICTION], diction)
AC_PATH_PROG([STYLE], style)
AC_PATH_PROG([LINKCHECKER], linkchecker)
AC_PATH_PROG([A2X], a2x)
AC_PATH_PROG([XMLTO], xmlto)
AC_PATH_PROG([MOGRIFY], mogrify)
AC_PATH_PROG([SOURCEHIGHLIGHT], source-highlight)
AC_PATH_PROG([ZIP], zip)
AC_CHECK_LIB([m], [pow])

AC_LANG([C++])

PKG_CHECK_MODULES([GTK], [gtk+-3.0],
   [
     AC_CHECK_LIB([gtk-3], [gtk_main])
     CFLAGS="$CFLAGS -DGTK_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DGSEAL_ENABLE"
   ],
   [
     PKG_CHECK_MODULES([GTK], [gtk+-2.0],
     [ 
         AC_CHECK_LIB([gtk-x11-2.0], [gtk_main])
     ], AC_MSG_WARN(Cannot find GTK: Is pkg-config in path?))
   ]
)

CFLAGS="$CFLAGS $GTK_CFLAGS"
CPPFLAGS="$CPPFLAGS $GTK_CFLAGS"
LIBS="$LIBS $GTK_LIBS"

AC_CHECK_LIB([curses], [initscr],
    [
      CPPFLAGS="$CPPFLAGS -I/curses"
      LIBS="$LIBS -lcurses"
    ] ,
    [  
      AC_CHECK_LIB([ncurses], [initscr],
          [
            CPPFLAGS="$CPPFLAGS -I/ncurses"
            LIBS="$LIBS -lncurses"
          ],
          [
            AC_CHECK_LIB([pdcurses], [initscr], [
            CPPFLAGS="$CPPFLAGS -I/pdcurses"  
            LIBS="$LIBS -lpdcurses"
          ] ,
          [
            AC_MSG_WARN([Cannot find curses])
          ])
    ])
])

AC_CHECK_LIB([pthread],[main])
AC_CHECK_LIB([gslcblas],[cblas_dgemm])
#AC_CHECK_LIB([gsl],[gsl_blas_dgemm])
AC_CHECK_LIB([gsl],[main])

AC_CHECK_LIB([newmat],[main], [
                      CPPFLAGS="$CPPFLAGS -I/newmat"
                      LIBS="$LIBS -lnewmat"
                      AC_CHECK_HEADERS([newmat/newmat.h])
])

AC_CHECK_LIB([itpp],[main], [
                      CPPFLAGS="$CPPFLAGS -I/itpp"
                      LIBS="$LIBS -litpp"
                      AC_CHECK_HEADERS([itpp/itbase.h])
])

AC_CHECK_PROG(QUANTLIB,quantlib-config,yes)
if test x"${QUANTLIB}" == x"yes" ; then
    # use quantlib-config for QL settings
    pkg_cxxflags=`quantlib-config --cflags`
    CFLAGS="$CFLAGS $pkg_cxxflags"
    pkg_libs=`quantlib-config --libs`
    LIBS="$LIBS $pkg_libs"
    pkg_version=`quantlib-config --version`

    # also test for quantlib version using result from quantlib-config --version
    case ${pkg_version} in
    0.1.*|0.2.*|0.3.*|0.4.*|0.8.*|0.9.*|1.0.*|1.1.*|1.2.*|1.3.*)
        AC_MSG_WARN([OptionMatrix needs QuantLib (>= 1.4.0).])
        ;;
    esac

    # now use all these
    AC_SUBST([CXXFLAGS],["${CXXFLAGS} "])
    AC_SUBST([CXXFLAGS],["${CXXFLAGS} ${pkg_cxxflags} ${gxx_newer_than_45}"])
    AC_SUBST([LDFLAGS],["${LDFLAGS} $pkg_libs"])
else
    AC_MSG_WARN([Installation of QuantLib will enable more financial models])
fi

## check for boost, this segment as well as segment below are 
## from QuantLib's configure.ac
## 
##
## Help the compiler find external software
AC_ARG_WITH([boost-include],
            AS_HELP_STRING([--with-boost-include=INCLUDE_PATH],[Supply the location of Boost header files]),
            [ql_boost_include_path=$withval],
            [ql_boost_include_path=""])
if test [ -n "$ql_boost_include_path" ] ; then
   AC_SUBST([CXXFLAGS],["${CXXFLAGS} -I${ql_boost_include_path}"])
fi
AC_ARG_WITH([boost-lib],
            AS_HELP_STRING([--with-boost-lib=LIB_PATH],[Supply the location of Boost libraries]),
            [ql_boost_lib_path=$withval],
            [ql_boost_lib_path=""])
if test [ -n "$ql_boost_lib_path" ] ; then
   AC_SUBST([LDFLAGS],["${LDFLAGS} -L${ql_boost_lib_path}"])
fi
##
## Check for Boost components
# QL_CHECK_BOOST_DEVEL
# --------------------
# Check whether the Boost headers are available
AC_DEFUN([QL_CHECK_BOOST_DEVEL],
[AC_MSG_CHECKING([for Boost development files])
 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/version.hpp>
     @%:@include <boost/shared_ptr.hpp>
     @%:@include <boost/assert.hpp>
     @%:@include <boost/current_function.hpp>]], [[]])],[AC_MSG_RESULT([yes])],[AC_MSG_RESULT([no])
     AC_MSG_WARN([Boost development files needed if using QuantLib])
    ])
])

# QL_CHECK_BOOST_VERSION
# ----------------------
# Check whether the Boost installation is up to date
AC_DEFUN([QL_CHECK_BOOST_VERSION],
[AC_MSG_CHECKING([for minimal Boost version])
 AC_REQUIRE([QL_CHECK_BOOST_DEVEL])
 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/version.hpp>]], [[@%:@if BOOST_VERSION < 103400
     @%:@error too old
     @%:@endif]])],[AC_MSG_RESULT([yes])],[AC_MSG_RESULT([no])
     AC_MSG_WARN([outdated Boost installation])
    ])
])

# QL_CHECK_BOOST
# ------------------------
# Boost-related tests
AC_DEFUN([QL_CHECK_BOOST],
[AC_REQUIRE([QL_CHECK_BOOST_DEVEL])
 AC_REQUIRE([QL_CHECK_BOOST_VERSION])
])
QL_CHECK_BOOST

# Checks for header files.
AC_CHECK_HEADERS([ql/quantlib.hpp])
AC_CHECK_HEADERS([boost/timer.hpp])
AC_CHECK_HEADERS([curses.h ncurses.h pdcurses.h])
AC_CHECK_HEADERS([ncurses/ncurses.h ncurses/curses.h pdcurses/pdcurses.h pdcurses/curses.h ])
AC_CHECK_HEADERS([float.h locale.h stddef.h stdlib.h string.h strings.h unistd.h getopt.h pthread.h sys/time.h math.h gsl/gsl_errno.h])
# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([atexit gettimeofday localeconv memset modf pow setlocale sqrt strstr])

if test $cross_compiling = no; then
  AM_MISSING_PROG(HELP2MAN, help2man)
else
  HELP2MAN=:
fi

AC_CONFIG_FILES([Makefile
                 src/models/abradford/Makefile
                 src/models/spinsky/Makefile
                 src/models/financialrecipes/src/Makefile
                 src/models/financialrecipes/examples/Makefile
                 src/models/metaoptions/src/Makefile
                 src/models/metaoptions/tests/Makefile
                 src/common/Makefile
                 src/curses/Makefile
                 src/gtk/Makefile
                 man/Makefile
                 doc/Makefile
                 doc/html/Makefile])
                 
AC_OUTPUT

AC_MSG_NOTICE([
------------------------------------------------------------------------------
Now type 'make ; sudo make install' to build and install $PACKAGE-$VERSION
See file README for more information.
------------------------------------------------------------------------------
])

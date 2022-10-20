#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([StockPrice], [1.0])

AC_CONFIG_SRCDIR([main.cc])
AC_CONFIG_HEADERS([config.h])

# Automake - non-recursive make mode
AM_INIT_AUTOMAKE([foreign 1.16 subdir-objects])
AC_CONFIG_FILES([Makefile])

# Automake - recursive make mode 
#AM_INIT_AUTOMAKE([foreign 1.16])
#AC_CONFIG_FILES([Makefile PriceTable/Makefile])

# C definitions in configuration header file
AC_ARG_ENABLE([fulltable],
	[AS_HELP_STRING([--enable-fulltable], [Enable print the negative price table])])

if test "${enable_fulltable}" = "yes" ; then
   AC_DEFINE([PRINT_NEGATIVE_TABLE], [1], [Print the values in negative table])
fi

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# library support
# With libtool support, don't need AC_PROG_RANLIB
# AC_PROG_RANLIB

# libtool support
AC_CONFIG_MACRO_DIRS([m4])
LT_PREREQ([2.4])
LT_INIT

AC_OUTPUT

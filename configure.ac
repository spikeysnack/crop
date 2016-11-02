#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([crop], [1.6], [spikeysnack@gmail.com])
AC_CONFIG_SRCDIR([src/crop.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR(.)

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET


# Checks for libraries.

AC_CHECK_LIB([gc], [GC_gcollect])
AC_CHECK_LIB([pthread], [pthread_create])


# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h sys/time.h syslog.h unistd.h gc/gc.h])


# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_UID_T

# adds options to configure script
CFLAGS=

# Add debugging
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [Enable debugging symols in compile ])],
    [], [enable_debug=no])
AM_CONDITIONAL([DEBUG], [test "x$enable_debug" != "xno"])
if test "x$enable_debug" != "xno"; then
    CFLAGS="$CFLAGS -ggdb3 -O0"
fi


# Check for Boehm GC
AC_ARG_WITH([boehm-gc],
    [AS_HELP_STRING([--with-boehm-gc],
        [Use the slower but more reliable conservative Boehm GC instead of GGGGC.])],
    [], [with_boehm_gc=no])
AM_CONDITIONAL([BOEHM_GC], [test "x$with_boehm_gc" != "xno"])
if test "x$with_boehm_gc" != "xno"; then
    LIBS="$LIBS -lgc"
    CFLAGS="$CFLAGS -DBOEHM_GC -DREDIRECT_MALLOC=GC_malloc"
fi



# --with-leak-detect
AC_ARG_WITH([leak-detect],
AS_HELP_STRING([--with-leak-detect],
	[enable libgc leak detection (debugging)]),
	[], [with_leak_detect=no])
AM_CONDITIONAL([WITH_LEAK_DETECT], test x"$with_leak_detect" != "xno")
if test "x$with_leak_detect" != "xno"; then
    LIBS="$LIBS -lgc"
    CFLAGS="$CFLAGS -DBOEHM_GC -DREDIRECT_MALLOC=GC_malloc -DFIND_LEAK"
    GC_FIND_LEAK=1    
    LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libgc.so
fi





# Checks for library functions.

AC_FUNC_FORK
AC_CHECK_FUNCS([strerror strndup strstr snprintf])

AC_CONFIG_FILES([src/Makefile Makefile])

LT_INIT
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE



AC_OUTPUT

#
# FreeArray Input Method Library
#
# Copyright (c) 2007-2010
# 	Yong-Siang Shih (Shaform) <shaform@gmail.com>
#
# FreeArray is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# FreeArray is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# See the file "COPYING" for information on usage and redistribution
# of this file.

m4_define([package_name], [libfreearray])

# if not 1, append datestamp to the version number.
m4_define([freearray_released], [0])
m4_define([freearray_major_version], [0])
m4_define([freearray_minor_version], [0])
m4_define([freearray_micro_version], [0])
m4_define(freearray_maybe_datestamp,
    m4_esyscmd([if test x]freearray_released[ != x1; then date +.%Y%m%d | tr -d '\n\r'; fi]))

m4_define([freearray_version],
    freearray_major_version.freearray_minor_version.freearray_micro_version[]freearray_maybe_datestamp)


AC_PREREQ(2.59)

AC_INIT([package_name], [freearray_version], [http://code.google.com/p/freearray/issues/entry])
AC_CONFIG_SRCDIR([src/imengine.cpp])
AC_CONFIG_MACRO_DIR([m4])


AM_INIT_AUTOMAKE([1.10])
AM_CONFIG_HEADER([include/config.h])
AC_PREFIX_DEFAULT([/usr])


LT_PREREQ([2.2])
LT_INIT([dlopen])


# define PACKAGE_VERSION_* variables
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O
AC_CHECK_FUNCS([memchr memmove memset setlocale strchr strcspn strdup strstr select])
AC_CHECK_HEADERS([locale.h stdlib.h string.h wchar.h])
AC_C_INLINE
AC_FUNC_MALLOC
AC_HEADER_STDBOOL
AC_PROG_MAKE_SET
AC_TYPE_SIZE_T


# check sqlite3
PKG_CHECK_MODULES(SQLITE3, [
    sqlite3
])


# OUTPUT files
AC_CONFIG_FILES([
Makefile
src/Makefile
include/Makefile
data/Makefile
icons/Makefile
tools/Makefile
test/Makefile
])

AC_OUTPUT

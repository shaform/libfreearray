#!/bin/sh
set -e
set -x
libtoolize
autoheader
aclocal -I m4
automake --add-missing --copy
autoconf
export CFLAGS="-g -O0"
export CXXFLAGS="$CFLAGS"
./configure

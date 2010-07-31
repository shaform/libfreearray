#
# FreeArray Input Method Library
#
# Copyright (c) 2010
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
# along with FreeArray.  If not, see <http://www.gnu.org/licenses/>.
#
# See the file "COPYING" for information on usage and redistribution
# of this file.

INCLUDES = \
	-I$(top_srcdir)/include \
	$(NULL)

lib_LTLIBRARIES = libfreearray.la
libfreearray_la_SOURCES = \
	kbtype.cpp \
	code.cpp \
	tables.cpp \
	imengine.cpp \
	imengine_component.cpp \
	frontend.cpp \
	$(NULL)

libfreearray_la_LIBADD = \
	$(top_builddir)/src/common/libcommon.la \
	$(top_builddir)/src/porting_layer/src/libporting_layer.la

libfreearray_la_LDFLAGS = \
	-version-info $(LIBFREEARRAY_CURRENT):$(LIBFREEARRAY_REVISION):$(LIBFREEARRAY_AGE) \
	-rpath $(libdir) \
	-no-undefined \
	-export-symbols-regex "^(freearray)_"


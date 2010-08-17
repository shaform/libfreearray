bin_PROGRAMS = test_imengine
test_imengine_SOURCES = \
	test_imengine.cpp \
	$(NULL)

test_imengine_CPPFLAGS = \
	-I$(top_srcdir)/include \
	@SQLITE3_CFLAGS@ \
	$(NULL)
test_imengine_LDADD = \
	../src/libfreearray.la
	$(NULL)

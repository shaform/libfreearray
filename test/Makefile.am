noinst_PROGRAMS = \
	       test_imengine \
	       test_tables \
	       $(NULL)
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

test_tables_SOURCES = \
	test_tables.cpp \
	$(NULL)

test_tables_CPPFLAGS = \
	-I$(top_srcdir)/include \
	@SQLITE3_CFLAGS@ \
	$(NULL)
test_tables_LDADD = \
	../src/libfreearray.la
	$(NULL)

ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = stockprice

stockprice_SOURCES = main.cc 
stockprice_CPPFLAGS = -I$(top_srcdir)/PriceTable
# Without libtool -- static library
#stockprice_LDADD = $(top_builddir)/PriceTable/libpricetable.a

# With libtool
stockprice_LDADD = $(top_builddir)/PriceTable/libpricetable.la

# Automake - non-recursive make mode
include $(top_srcdir)/PriceTable/Makefile.am

# Automake - recursive make mode
#SUBDIRS = PriceTable
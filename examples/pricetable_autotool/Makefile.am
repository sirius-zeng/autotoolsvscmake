ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = pricetable

pricetable_SOURCES = main.cc 
pricetable_CPPFLAGS = -I$(top_srcdir)/PriceTable
# Without libtool -- static library
#pricetable_LDADD = $(top_builddir)/PriceTable/libpricetable.a

# With libtool
pricetable_LDADD = $(top_builddir)/PriceTable/libpricetable.la

# Automake - non-recursive make mode
include $(top_srcdir)/PriceTable/Makefile.am

# Automake - recursive make mode
#SUBDIRS = PriceTable
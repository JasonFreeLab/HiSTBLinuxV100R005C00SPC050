## Makefile.am for DirectFB/inputdrivers/bluetooth

INCLUDES = -I$(top_builddir)/include	\
	   -I$(top_builddir)/lib	\
	   -I$(top_srcdir)/include	\
	   -I$(top_srcdir)/lib	        \
	   -I$(top_srcdir)/src

bluetooth_LTLIBRARIES = libdirectfb_bluetooth.la

if BUILD_STATIC
bluetooth_DATA = $(bluetooth_LTLIBRARIES:.la=.o)
endif

bluetoothdir = $(MODULEDIR)/inputdrivers

libdirectfb_bluetooth_la_SOURCES = bluetooth.c
libdirectfb_bluetooth_la_LDFLAGS = -module -avoid-version $(DFB_LDFLAGS)
libdirectfb_bluetooth_la_LIBADD  = $(top_builddir)/lib/direct/libdirect.la $(top_builddir)/src/libdirectfb.la

include $(top_srcdir)/rules/libobject.make
	

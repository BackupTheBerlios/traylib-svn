## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES = \
	$(GTK_CFLAGS) \
	-I../include/

libtraylib_la_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libtraylib.la

libtraylib_la_SOURCES = \
	eggtrayicon.h\
	trayicon.c\
	eggtrayicon.c

libtraylib_la_LDFLAGS = 

libtraylib_la_LIBADD =  \
	$(GTK_LIBS) \
	-lgthread-2.0

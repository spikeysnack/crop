AUTOMAKE_OPTIONS= subdir-objects
 
ACLOCAL_AMFLAGS = -I m4

SUBDIR= doc

bin_PROGRAMS = crop

crop_SOURCES = src/crop.c src/crop.h src/help.h src/options.h src/utils.h

dist_doc_DATA = doc/* 

dist_noinst_SCRIPTS = autogen.sh


TESTS = check_crop.sh 
 
install-data-hook:
	@sensible-browser file:///$(docdir)/crop.html


if DEBUG
if BOEHM_GC
BOEHM_GC_DEBUG = -DGC_DEBUG
AM_CFLAGS = $(BOEHM_GC_DEBUG)
endif
endif








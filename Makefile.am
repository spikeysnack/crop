AUTOMAKE_OPTIONS= subdir-objects
 
ACLOCAL_AMFLAGS = -I m4

SUBDIR= doc

bin_PROGRAMS = crop

crop_SOURCES = src/crop.c src/crop.h src/help.h src/options.h src/utils.h

man1_MANS = crop.1

dist_doc_DATA = doc/* 

dist_noinst_SCRIPTS = autogen.sh

TESTS = check_crop.sh 
#TESTS = test-driver

webbrowser = $(shell bash find_browser.sh)

# runs after install as normal user
install-data-hook:
	if [ -n $(webbrowser) ] ; then sudo -u ${SUDO_USER}  $(webbrowser) file:///$(docdir)/crop.html ; fi &


if DEBUG
if BOEHM_GC
BOEHM_GC_DEBUG = -DGC_DEBUG
AM_CFLAGS = $(BOEHM_GC_DEBUG)
endif
endif








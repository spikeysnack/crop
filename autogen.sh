#!/bin/sh


DEBUG=

ACLOCAL=`which aclocal`
AUTOHEADER=`which autoheader`
AUTOMAKE=`which automake`
AUTOCONF=`which autoconf`
AUTORECONF=`which autoreconf`


if [ "X" != "X"$AUTORECONF ]; then
    $AUTORECONF --force --install
fi

$ACLOCAL
$AUTOHEADER
$AUTOMAKE --add-missing
$AUTOCONF

$AUTORECONF  --install
mkdir -p build

if [ ! -z $DEBUG ]; then
    CFLAGS="-O0 -ggdb3 -DDEBUG -DREDIRECT_MALLOC=GC_malloc" ./configure -prefix=/usr/local --enable-debug --with-boehm-gc 
else
CFLAGS="-O2 -mtune=native --optimize-strlen " ./configure -prefix=/usr/local --enable-debug --with-boehm-gc 
fi


#CFLAGS="-O0"  ./configure -prefix=/usr/local --enable-debug --with-boehm-gc --with-leak-detect
#./configure 
#./configure --enable-debug 
#./configure --enable-debug --with-boehm-gc --with-leak-detect



echo
echo "if configure completed OK, type make." 
echo "if make works OK, then type sudo make install."
echo




# make

# sudo make install

# echo "testing crop"

# crop -l 

# crop -c

# sudo crop -d

# ps ax |grep crop

# ps exo comm,priority 

# tail -f ~/.crop/crop.log &

# sudo crop -k

# killall -SIGHUP tail



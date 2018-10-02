#!/bin/bash

YesNo() 
{
# call with a prompt string or use a default
    read -r -p "${1}" response
    case "$response" in
        [yY][eE][sS]|[yY]|"" ) 
#	    >&2 echo "YES"
	    echo "y"
           ;;
        *)
	    echo "n"
            ;;
    esac
}


PREFIX=/usr/local

response=$(YesNo "Install with sudo to [/usr/local/] ? [Y/n] ") 

if [ $response == "y" ] ; then
    
    PREFIX=/usr/local
    SUDO=$(which sudo)
else
    response=$(YesNo "Install to [${HOME}] ? [y/N] ") 

    if [ $response  == "y" ] ; then
	SUDO=
	PREFIX=${HOME}
    else
	>&2 echo "I don't know what to do."
	exit
    fi
fi




CONFIG="--prefix ${PREFIX} --with-gnu-ld"

DEBUG=
BOEHMGC=

ACLOCAL=`which aclocal`
AUTOHEADER=`which autoheader`
AUTOMAKE=`which automake`
AUTOCONF=`which autoconf`
AUTORECONF=`which autoreconf`

echo "Updating configuration files ..."

if [ "X" != "X"$AUTORECONF ]; then
    $AUTORECONF --force --install
fi


echo "localizing ..."
$ACLOCAL
echo "creating headers ../"
$AUTOHEADER
echo "creating Makefile ..."
$AUTOMAKE --add-missing
echo " configuring build ..."
$AUTOCONF
echo " reconfiguring for installation ..."
$AUTORECONF  --install


#default
CFLAGS="-std=c99 -O2 -mtune=native --optimize-strlen" 

echo  "checking build system ..."
if [ ! -z $DEBUG ]; then

    CFLAGS="-O0 -ggdb3 -DDEBUG"  ./configure ${CONFIG} --enabl-debug

fi

if [ ! -z $BOEHM ]; then

    CFLAGS="${CFLAGS} -DBOEHMGC" ./configure ${CONFIG} --with-boehm-gc 

else
     CFLAGS="${CFLAGS}"  ./configure ${CONFIG}  
fi




#CFLAGS="-O0"  ./configure -prefix=/usr/local --enable-debug --with-boehm-gc --with-leak-detect
#./configure 
#./configure --enable-debug 
#./configure --enable-debug --with-boehm-gc --with-leak-detect


echo "compiling ..."
make

echo

response=$(YesNo "Install now?  [Y/n]") 

if [ $response == "y" ] ; then

    ${SUDO} make install
else
    if [[ $SUDO ]] ; then 

	echo "OK.  to install type \'sudo make install\'"
    else
	echo "OK.  to install type \'make install\'"
    fi
fi




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



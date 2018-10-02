#!/usr/bin/env bash

[[ ! -f ./crop ]] && >&2 echo "crop Not Found" && exit


DIRLIST="ls --format=vertical -R -w 40"


# show dir with lines
dir_list()
{
    if [ $# -gt 1 ] ; then
	DOGREP=" | grep ${1}"
    fi

    echo "-----------------------------------"
    $DIRLIST $DOGREP
    echo "-----------------------------------"	
    echo
}





rm -rf  test
mkdir -p "test"
cd test

touch Ant_dog  Bagel_dog  Cat_dog  Dog  Eagle_dog  
touch "Some Long Thing" "A File File with extra File stuff.txt"

dir_list 

echo "remove \'_dog\' from files (Y)"
yes Y |    ../crop "_dog"  *
 
dir_list 

echo "remove \'File\' from files (1)"

yes Y | ../crop "File" * 

dir_list "File"

echo "remove ALL \'File\' from files (1)"

yes Y | ../crop -a "File" * 

dir_list "File"


echo "remove \'g\' from files (N)"
yes N | ../crop "g" *

dir_list 

cd ..

rm -f test



# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4

# emacs               #
# Local Variables:    #
# mode: shell-script  #
# mode: font-lock     #
# tab-width:8         #
# End:                #






   

  

#!/bin/bash

#echo "-----------------------------------"
#ls --format=vertical -w 40
#echo "-----------------------------------"

#echo "[INTERACTIVE REPLACE]"
#echo -e "${RESPONSE}" | ./replace  -i .txt .REPLACED *

PASS=0
SKIP=77
FAIL=1
HARDERR=99

# check for crop
if [ ! -x "../crop" ] ; then
    exit $HARDERR
fi


# all one line to preserve wd
mkdir -p test

cd test     

touch                  \
    "This Is 1.test"  "This Is 2.test"  "This Is 3.test"  "This Is 4.test"  \
    "Yes This Is Too.test"                          \
    "But This Isn't 1.test"                         \
    "This Is a File Has [brackets].txt"             \
    "This    file has spaces in bad   places . txt" \
    'this is a file with no suffix'                 \
    "Sign Of Truth (Japan).cue"     ;               

ls -1 *.test 

echo "[[TEST 1]] -- basic prefix crop"
REPONSE='Y\n'
../crop  -f "This Is"  * 

if [ ! -f "Yes Too.test" ] ; then
    exit $FAIL
fi

#ls -1 *.test          


echo "[[TEST 2]] -- embeded string crop"     
../crop -f "Japan" *     


if [ ! -f "Sign Of Truth ().cue" ] ; then
    exit $FAIL
fi
#ls -1 *.test          

echo "[[TEST 3]] -- remove parentheses"
../crop -f "()" *   

if [ ! -f "Sign Of Truth.cue" ] ; then
    return $FAIL
fi

echo "[[TEST 4]] -- scrub filenames"
../crop -f ""   * 

if [ ! -f "This file has spaces in bad places.txt" ] ; then 
    return $FAIL
fi

#ls -1 *

cd ..
rm test/*
rm -r test

exit $PASS



#!/bin/bash

browser_list="xdg-open sensible-browser x-www-browser chromium-browser google-chrome lynx xlinks xlinks2"; 

for B in ${browser_list} 
do 
    BROWSER=$(which "$B")  
    if [[ "$BROWSER" ]] ; then 
	echo "${BROWSER}"; 
	break; 
    fi
done 


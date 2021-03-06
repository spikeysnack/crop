![alt text][logo]

[logo]: https://github.com/spikeysnack/crop/blob/master/doc/crop.png "crop"

## crop removes a matching string from a list of filenames.

###VERSION
crop version:	 1.6  date:	10 Nov 2017
=======
### VERSION
crop version:	 1.6  date:	10 Nov 2016

### INSTALLATION
	The binary crop is installed in /usr/local/bin/crop
	The man page goes in /usr/local/share/man/man1/crop.1
	The documentation goes in /usr/local/doc/crop/

	requirements:
	gcc or clang compiler
	standard C developement libraries and headers	
	(no external libs required)

	type:
		make
		make test
		make install 
		(sudo required for install -- 
		 you will be asked for oyour password)


### USAGE
<pre>
	usage: crop < string > < filename1 > < filename2 > ...

	options:
		 -a remove all matches from filename, (not just first match) 
	 	-f force rename (non-interactive)  
	 	-h help 
	 	-q quiet 
	 	-v version 
	note: (*) processes all files in current dir
</pre>


	EXAMPLE:	 to remove 'doug' from dougdog.txt 
	 crop doug dougdog.txt 
	 dougdog.txt  ==> dog.txt  

### EXPLANATION 

I like to arrange my digital music collection thusly:
<pre>
   FORMAT
	 ARTIST
		ALBUM
		      FILES
</pre>
So I have directories like so:
<pre>
   FLAC/
	 Yes/
 	      Going For The One/
				  Going For the One.flac 
				  Going For the One.cue 
				  Going For the One.log
				  Going For the One.txt
				  Front.jpg
				  Back.jpg
				  Inlay.jpg
				  Disc.jpg
</pre>  

But more often than not the files come in a Roshell archive (rar) like so:
<pre>
Yes - Going For The One - 1973 - Going For the One.flac 
Yes - Going For The One - 1973 - Going For the One.cue 
Yes - Going For The One - 1973 - Going For the One.log
Yes - Going For The One - 1973 - Going For the One.txt
Yes - Going For The One - 1973 - Front.jpg
Yes - Going For The One - 1973 - Back.jpg
Yes - Going For The One - 1973 - Inlay.jpg
Yes - Going For The One - 1973 - Disc.jpg
</pre>
or 
<pre>
BIG_FREAKIN_ARCHIVE_OF_KORKOVSKI_IS_THE_MAN.COM!!!!_Going For the One.flac
BIG_FREAKIN_ARCHIVE_OF_KORKOVSKI_IS_THE_MAN.COM!!!!_Going For the One.cue
BIG_FREAKIN_ARCHIVE_OF_KORKOVSKI_IS_THE_MAN.COM!!!!_Going For the One.jpg
BIG_FREAKIN_ARCHIVE_OF_KORKOVSKI_IS_THE_MAN.COM!!!!_Going For the One.txt
...
</pre>
--> just all kinds of wrong.


So Microsoft Windows 7 has a handy feature for renaming files 
by hitting F2,editing, and then  hitting tab again 
to rename the next file automatically,
and sometime you have to do each file separately, 
but if I do something so many times per week, 
I want to automate it somewhat.


crop allows you to cut out a substring 
from the name of a group of files
while ignoring files without the matching string.


In the above case I would invoke it like this:
```bash
   crop -f Yes\ \-\ Going\ For\ The\ One\ \-\ 1973\ -\  *  
```
and the string "Yes - Going For The One - 1973 - " 
would be removed from all filenames in the dir.

It is tricky with the dashes and spaces,
but a double space before the * makes it work, 
and bash auto-expands the backslashes with 
a one or two character tap of the <tab> key. 
If you get it wrong nothing much happens. 

You must explicitly force autorenaming because
it takes some experiece to gain confidence in the tool 
that you aren't going to hurt your files, 
but it becomes a real time-saver for bulk renaming files
with unwanted common strings in them.

If a mistake is made and you end up with a file that starts with
some bad character like a space or a dash, remember that GNU getops
stops parsing after a double dash (--) 
and treats the rest of the line as regular args. 

### ENJOY, IMPROVE, 
       Chris

Click on Picture Below for Demo Video <b>"Cropping Arcadia"</b>.

[![Cropping Arcadia](https://s25.postimg.org/53t5baunj/mpv-shot0001.jpg)](https://vimeo.com/231978052)

/* help.h */

/* friendly messages */

#ifndef _HELP_H_

#include <stdio.h>

void usage   (FILE* f);
void help    (FILE* f);
void version (FILE* f);


/* usage message */
void usage(FILE* f)
{
  version( f );
  fprintf( f, "usage: crop <string> <filename1> <filename2> ...\n");
  fprintf( f, "options:\n\t -a remove all matches from filename, (not just first match) \n");
  fprintf( f, "\t -f force rename (non-interactive)  \n");
  fprintf( f, "\t -h help \n");
  fprintf( f, "\t -q quiet \n");
  fprintf( f, "\t -v version \n");
  
  fprintf( f, "\tnote: (*) processes all files in current dir\n");
}

void help(FILE* f)
{
  fprintf( f, "crop removes a matching string from a list of filenames.\n" ); 
  usage( f );
  fprintf( f, "\n\tEXAMPLE:\t to remove \'doug\' from dougdog.txt \n" ); 
  fprintf( f, "\t crop doug dougdog.txt \n" );
  fprintf( f, "\t ==> dog.txt \n" ); 
}


void version(FILE* f)
{

#ifndef CROP_VERSION
#error CROP_VERSION is not Defined yet
#endif
  fprintf( f, "%s version:\t %s  date:\t%s\n", "crop",  CROP_VERSION, CROP_DATE );

}


#define _HELP_H_
#endif

/*END*/

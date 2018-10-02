/* options.h */

/* 
 * getopt options 
 * "man 3 getopt" 
*/

/* AUTHOR:  Chris Reid <spikeysnack@gmail.com> */
/* LICENSE: Free for all purposes              */
/* COPYRIGHT: 2017- Chris Reid                 */


#ifndef _OPTIONS_H_

#include <unistd.h>
#include "help.h"

void options ( int argc, char** argv);
int getopt(int argc, char * const argv[],
	   const char *optstring);


/* some C suites do not define bool */                                                                                                                       
#ifndef bool
typedef enum{false, true} bool;
#endif

/* 
 * define some boolean flags (global variables)
*/
bool all_matches  = false;
bool force_rename = false;
bool quiet_rename = false;

extern char* replacement;


/*  
 * options   
 * (a)ll  
 * (f)orce 
 * (h)elp 
 * (q)uiet  
 * (v)ersion 
*/
void options ( int argc, char** argv)
{
  int opt;
  opt = 0;

  while ((opt = getopt(argc, argv, "afhqv")) != -1) 
    {
      switch (opt) {
	
      case 'a':
	all_matches = true;
	break;
	
      case 'f':
	force_rename = true;
	break;

      case 'h':
	help(stdout);
	break;

      case 'q':
	quiet_rename = true;
	break;

      case 'v':
	version(stdout);
	exit(EXIT_SUCCESS);
	break;
	
      default: /* '?' */
	usage(stderr);
	exit(EXIT_FAILURE);
	
      }// switch(opt)
      
    }//while(opt)
  
}/* options */


#define _OPTIONS_H_
#endif

/*END*/

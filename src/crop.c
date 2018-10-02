/* crop.c */
/* removes a leading substring from a list of files */

/* AUTHOR:  Chris Reid <spikeysnack@gmail.com> */
/* LICENSE: Free for all purposes              */
/* COPYRIGHT: 2017- Chris Reid                 */

/* The main workhorse funtions are in crop.h and utils.h. */



#define CROP_VERSION       "1.6"
#define CROP_DATE          "01 Nov 2017"

#include<locale.h>

#include "crop.h"

/* function declarations */
void options ( int argc, char** argv);
void args( int nonoptargc, char* match, char** nonoptargs );
int main ( int argc, char** argv, char** env);

/* external variables */
extern int optind; /* unistd.h */
extern char* optarg; /* unistd.h */


int main ( int argc, char** argv, char** env)
{

  int    nonoptargc;
  char*  match;
  char** nonoptargs;

  /* we won't get unkown characters */
  /* if we set baseline locale to C */
  setlocale(LC_CTYPE, "");

  /* gotta have at least 2 arguments */
  if (argc  < 2 )
    {
      usage(stderr);
      exit(0);
    }

  /* get the command options */
  options( argc, argv );

  
  /* optind is the number of options (from unistd.h) */
  if ( optind > 1 ) 
    {
      nonoptargs = argv + ( optind ) ;
      nonoptargc = argc - ( optind ) ;
      match = nonoptargs[0];
    }
  else
    {
      nonoptargs = argv;
      nonoptargc = argc;
      match = argv[1];

    }

#ifdef DEBUG_OPTS
  fprintf(stderr, "new nonoptargs[0]:\t %s\nnew argc = %d\nmatch = %s\n", nonoptargs[0], nonoptargc, match );      
  fflush(stderr);
#endif

  /* find matches and rename them */
  args( nonoptargc, match, nonoptargs );

  return 0;

} /* main */


/*END*/


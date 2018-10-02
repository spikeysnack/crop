/* utils.h */

/* 
 * some utlity options 
 * for basic operations
 */

/* AUTHOR:  Chris Reid <spikeysnack@gmail.com> */
/* LICENSE: Free for all purposes              */
/* COPYRIGHT: 2015- Chris Reid                 */


#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include "options.h"


/*-------------------------------------*/
/*  MACROS                             */
/*  some macros for strings            */

/* handle NULL strings (strlen won't) */
#define strlen(s) ( (s==NULL)?0:strlen(s) )  

#define NEW_STRING( sz )  \
  (char*) calloc( (sz) +1 , sizeof(char) ) 

#define NEW_STRING_ARRAY( sz )  \
  (char**) calloc( (sz) +1 ,  sizeof(char*) )


#define  FREE_STRING( S ) free( (S) ); (S) = NULL;

#define  FREE_STRING_ARRAY( SA ) \
  do { int i = 0; while ( SA[i] != NULL) { free(SA[i]); i++; } } while(0); \
     (SA) = NULL;



/*-------------------------------------*/
/*  function definitions               */
/*  and constants                      */

bool file_exists(const char* filename);

bool get_response(void);

bool rename_file ( const char* filename, const char* newname );


/*-------------------------------------*/
/*  functions                          */



/*-------------------------------------*/
/* file_exists                         */
/* hack to check existence of a file   */
/*                                     */
/* INPUT                               */
/*       filename:char*                */
/*                                     */
/* OUPUT                               */
/*      bool: true if file exists      */

bool file_exists(const char* filename)
{
  int err = 0;
  char * errstring = NULL;
  bool ret = false;
  
  assert (filename != (char*) NULL );
  
  errno = 0;
  
  
  if ( access( filename , F_OK ) == 0 ) //check for existence
    {      
      ret = true;
    }
  else
    {
      err = errno;
      if ( errno != ENOENT )
	{
	  errno = 0;
	  errstring = strerror(err);
	  perror(errstring);
	  ret = false;
	}
      else
	{
	  ret = false;
	}

    }// if
  
  return ret;
}






/*-------------------------------------*/
/* rename_file                         */
/* renames files                       */
/*                                     */
/* INPUT                               */
/*       filename: char*               */
/*       newname:  char*               */
/*                                     */
/* OUPUT                               */
/*      bool: true if file renamed     */
/*                                     */ 
/* NOTE                                */
/* boolean wrapper for rename function */

bool rename_file ( const char* filename, const char* newname )
{
  int err;
  int ret = false;
  size_t flen = 0;
  size_t nlen = 0;
  
  char* errstring = NULL;
  
  
  flen = strlen(filename);
  nlen = strlen(newname);
  
  errno = 0;
  
  if( flen == nlen )
    if (strncmp( filename , newname, flen ) == 0 )
      {
	if (! quiet_rename) fprintf(stdout , "%s and %s are the same .. skipping.  \n", filename, newname ); 
	ret = false;
	goto bye;
      }
  

#ifdef DEBUG
  fprintf(stderr, "rename_file: filename: %s \t newname: %s\n" , filename, newname );
  fflush (stderr);
#endif


  if ( (file_exists( filename )) && (access(filename, W_OK) == 0) ) 
	{

	  if (! force_rename )
	    {
	      printf("[ %s ==> %s (y/n)? ]", filename , newname );
	      
	      if ( ! get_response() )  
		{
		  ret= false;
		  goto bye;
		}
	    } 

	  if ( rename( filename, newname ) == 0 ) 
	    { 
	      if (! quiet_rename) fprintf(stdout , "%s ==> %s \n", filename, newname ); 
	      ret = true;
	    }
	  else
	    {
	      err = errno;
	      errno = 0;
	      errstring = strerror(err);
	      perror(errstring);
	      ret = false;
	    }
	  
	} /* file exists */
      else
	{
	  err = errno;
	  errno = 0;
	  errstring = strerror(err);
	  perror(errstring);	  
	  ret = false; 
	} //top if

 bye:      
  return ret;
}/*rename file*/
      





/*-------------------------------------*/
/* get_response                        */
/* ask user for Y or y , N or n        */
/*                                     */
/* INPUT                               */
/*       none                          */
/*                                     */
/* OUPUT                               */
/*      bool: true if Y or y           */

bool get_response()
{

  char p = '\0';

  fflush (stdin);

  if (  scanf ("%c", &p) == EOF ) return false;


  if ( (p == 'Y') || ( p == 'y') ) return true;
      
  return false;

}/* get_response */




#endif

/*END*/





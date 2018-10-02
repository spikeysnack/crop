/* crop.h */

/* AUTHOR:  Chris Reid <spikeysnack@gmail.com> */
/* LICENSE: Free for all purposes              */
/* COPYRIGHT: 2017- Chris Reid                 */


#ifndef CROP_H
#define CROP_H

#include <stdlib.h>  /* free, calloc, exit */
#include <string.h>  /* strlen, strcmp, strstr, memmove */  
#include <ctype.h>   /* isspace , etc */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


extern char *strdup(const char *s);
extern char *strndup(const char *s, size_t n);

#include "options.h"
#include "utils.h"


/* function declarations */

void  args (int numargs, char* match, char** arglist );
char* substring( const char* str, const char* match);
char* all_substrings ( const char* str, const char* match);
char* ltrim(char* s) ;
char* rtrim(char* s) ;
char* trim( const char* str);
char* compress_spaces(const char *str);
bool  file_exists(const char *filename); 


/* external variables */
extern bool all_matches; /*(options.h)*/
extern bool force_rename;/*(options.h)*/
extern bool quiet_rename;/*(options.h)*/


/*-------------------------------------*/
/* args                                */
/*    process non opt args             */
/*                                     */
/* INPUT                               */
/*      numargs: int   arg count       */
/*      match:   char*   match string  */
/*      arglist: char**                */
/*                                     */
/* OUPUT                               */
/*      none                           */
/* NOTE                                */ 
/*     sets flags and vars             */ 

void  args (int numargs, char* match, char** arglist )
{

  int i;
  char *newnm = NULL;

  if ( (!numargs) || (!match) || (!arglist) )
    {
      usage(stderr);
      exit(0);
    }


  /* assert( numargs > 0 ); */
  /* assert ( match != (char*) NULL  ); */
  /* assert ( arglist !=(char**) NULL); */


  for (i = 1; i < numargs ; i++ )
    {

      if ( strcmp( arglist[i] , match ) == 0 ) continue; /* same name skip */

      if ( all_matches )
	newnm = all_substrings( arglist[i], match );
      else
	newnm = substring( arglist[i], match );
      
      
      if ( ! newnm ) continue;	/* no match --  skip */
      
      newnm = trim(newnm);
      
      rename_file ( arglist[i], newnm );
      
    } /*for */

  if (newnm) FREE_STRING(newnm);

}/* args */




/* return a string with the matching string removed */

char* substring( const char* str, const char* match)
{

  size_t nstr_sz = 0;
  int mlen, slen, sublen, start, end, err;
  char* tmp = NULL;
  char* sub = NULL;  

  assert( str != (char*)NULL);
  assert( match != (char*)NULL);

  mlen = slen = sublen = start = end = err = 0;

  errno = 0;

  mlen = strlen(match);

  slen = strlen(str);

  nstr_sz = (slen - mlen) + 1; // substring is smaller
  
  if ( slen < mlen ) return(char*) NULL;  // can't match -- bail


  sub = strstr(str, match);  // find  first match or NULL 
  /* NOTE strsrtr does not allocate memory, 
     it points to match in str. So don't free sub. 
  */

  if ( sub )  // match
    {

      if( ! (tmp = NEW_STRING(nstr_sz)) )   // create chars  
	{ // calloc failed
	  err = errno;
	  char errstring[256];
	  snprintf(errstring, sizeof errstring, "%s%s%s", "substring: Calloc Failed:\t", strerror(err), "\n");
	  perror (errstring );      
	  errno = 0;
	  exit(-1);
	}

      sublen  = strlen(sub);
      start = slen - sublen;
      end   = slen - mlen;

      memmove(tmp, str, start  ); //first bytes before match

      memmove(tmp+start, sub+mlen, end  ); //last bytes after match

      return tmp;
    }   

  
      return (char*)NULL; // no match      


}/*substring*/



char* ltrim(char* s) 
{
  char* newstart = s;

  while (isspace( *newstart)) {
    ++newstart;
  }

  // newstart points to first non-whitespace char (which might be '\0')
  memmove( s, newstart, strlen( newstart) + 1); // don't forget to move the '\0' terminator

  return s;
}


char* rtrim( char* s)
{
  char* end = s + strlen( s);

  // find the last non-whitespace character
  while ((end != s) && isspace( *(end-1))) {
    --end;
  }

  // at this point either (end == s) and s is either empty or all whitespace
  //      so it needs to be made empty, or
  //      end points just past the last non-whitespace character (it might point
  //      at the '\0' terminator, in which case there's no problem writing
  //      another there).    
  *end = '\0';

  return s;
}


char*  trim(const char* s)
{
  char *a , *b , *p;
  char *at , *bt;
  size_t  s_sz, a_sz, b_sz , p_sz;


  s_sz = strlen(s);

  p = strchr( s, '.');
  
  if (p)
    {
      p_sz = strlen(p);

      a = strndup( s, ( s_sz - p_sz) );
      a_sz = strlen(a);
      b = strndup( p+1, ( s_sz - a_sz) );
    
      char* t = NEW_STRING(s_sz);
  
      at = rtrim(a);
      a_sz = strlen(at);
      bt = ltrim(b);
      b_sz = strlen(bt);
      strncpy(t, at , a_sz );
      strncat(t, "." , 1 );
      strncat(t, bt , b_sz );
      return compress_spaces(t);
    }
  else
    return compress_spaces(s);
}//trim






/* eliminate any more than single spaces in a string */
char* compress_spaces(const char* src)
{
  char* dst = NULL;
  char* ret = NULL;
  size_t slen, rlen;

  slen = strlen(src);
  dst = (char*) NEW_STRING( slen );
  ret = dst;

  for (; *src; ++dst, ++src) {
    *dst = *src;
    if (isspace(*src))
      while (isspace(*(src + 1)))
	++src;
  }
  *dst = '\0';
 
  slen = strlen(src);
  rlen = strlen(ret);

  if ( rlen < slen )
    ret = realloc( ret, rlen + 1 );

  return ret;
}


/* recursive substring finds all matches */

char * all_substrings ( const char* str, const char* match)
{
  
  char* sub;
  char* acc = (char*) NULL;

  sub = substring(str, match);
  
  while (sub)
    {
      acc = strdup(sub);  
      sub = substring(acc, match);      
    }
    
  return acc;
}
/* all_substrings */

#endif

/*END*/




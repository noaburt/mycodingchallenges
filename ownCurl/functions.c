
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the functions file for this coding challenge

*/

#include <main.h>


parsedurl* parseURL(char* fullurl) {

  /* parse inputted url and return struct containing parsed data */

  char* urlptr = fullurl;

  if ( !fullurl ) {
    errx(1, "url pointer is NULL");
  }

  parsedurl* parsed = malloc( sizeof( parsedurl* ) );

  while ( *urlptr != ':' ) {
    /* find end of protocol */

    urlptr++;
  }

  
  switch( (char) *(urlptr - 1) ) {  
  case 's': parsed->protocol = HTTPS; break;
  case 'p': parsed->protocol = HTTP; break;
  default: errx(1, "no protocol identified"); break;
  }

  /* skip :// and get host name and port */
  
  urlptr += 2;
  while ( *urlptr != '/' && *urlptr != ':' ) {
    if ( *urlptr == ':' ) {
      // GET PORT
    }

    // OTHERWISE GET HOST
    
    urlptr++;
  }
  
  return parsed;
}

int freeurl(parsedurl* parsed) {
  /* free pointers stored by parsed url structure */

  if ( !parsed ) {
    return 1;
  }

  free(parsed->host);
  free(parsed->path);

  return 0;
}

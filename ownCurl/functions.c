
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

  parsedurl* parsed = malloc( sizeof(*parsedurl) );

  while ( *urlptr != ':' ) {
    /* find end of protocol */

    urlptr++;
  }

  switch( *(urlptr - 1) ) {
  case 's': parsed->protocol = HTTPS;
  case 'p': parsed->protocol = HTTP;
  default: errx(1, "no protocol identified");
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

void* freeurl(parsedurl* parsed) {
  /* free pointers stored by parsed url structure */

  if ( !parsed ) {
    return;
  }

  free(parsed->protocol);
  free(parsed->host);
  free(parsed->path);
  free(parsed->port);

}

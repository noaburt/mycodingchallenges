
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the functions file for this coding challenge

*/

#include <main.h>


/* url */

parsedurl* parseURL(char* fullurl) {

  /* parse inputted url and return struct containing parsed data */

  /* check for NULL url */
  char* urlptr = fullurl;

  if ( !fullurl ) {
    errx(1, "url pointer is NULL");
  }

  parsedurl* parsed = malloc( sizeof( parsedurl* ) );

  /* find end of protocol */
  while ( *urlptr != ':' ) { urlptr++; }

  /* assign protocol bassed on http(s) or htt(p) */
  switch( (char) *(urlptr - 1) ) {  
  case 's': parsed->protocol = HTTPS; break;
  case 'p': parsed->protocol = HTTP; break;
  default: errx(1, "no protocol identified"); break;
  }

  /* skip '://' and get host name and port */
  urlptr += 3;

  /* read host until '/' is reached, store host */
  parsed->host = malloc( sizeof( char* ) );

  char* readptr = parsed->host;
  char* portptr = "80";
  
  while ( *urlptr != '/' ) {

    if ( *urlptr == ':') {
      /* finish reading host, store, and begin reading port */
      *readptr = '\0';
      readptr = portptr;
    } else {
      /* otherwise store current char to readptr*/
      *readptr = *urlptr;
      readptr++;
    }
    
    urlptr++;
    
  }

  *readptr = '\0';
  parsed->port = strtol( portptr, '\0', 10 );
  
  /* store the rest of the url as path*/
  parsed->path = malloc( sizeof( char* ) );
  char* pathptr = parsed->path;

  while ( *urlptr != '\0' ) {
    *pathptr = *urlptr;

    pathptr++;
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

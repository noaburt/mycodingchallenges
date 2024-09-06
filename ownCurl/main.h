
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the header file for this coding challenge

*/

/* includes */

#include <stdio.h>
#include <err.h>


/* structs */

typedef struct PARSEDURL {

  /* struct to store parts of url for requests */

  enum PROTOCOL {HTTP, HTTPS} protocol;
  
  char* host;
  char* path;

  long port;
  
} parsedurl;


/* functions */

parsedurl* parseURL(char* fullurl);
void* freeurl(parsedurl* parsed);


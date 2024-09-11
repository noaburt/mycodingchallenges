
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the header file for this coding challenge

*/

/* includes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostname */


/* structs */

typedef struct PARSEDURL {

  /* struct to store parts of url for requests */

  enum PROTOCOL {HTTP, HTTPS} protocol;
  
  char* host;
  char* path;

  long port;
  
} parsedurl;


/* functions */

/* url */
parsedurl* parseURL(char* fullurl);
int freeurl(parsedurl* parsed);

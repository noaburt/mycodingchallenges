
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
#include <unistd.h>
#include <err.h>
#include <sys/socket.h> /* for: socket, connect */
#include <netinet/in.h> /* for: struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* for: struct hostent, gethostname */


/* structs */

typedef struct FLAGS {

  /* struct to store flags enabled / disabled */

  int help;
  int verbose;
} flags;

typedef struct PARSEDURL {

  /* struct to store parts of url for requests */

  enum PROTOCOL {HTTP, HTTPS} protocol;
  
  char* host;
  char* path;

  long port;
  
} parsedurl;


/* functions */

/* flags & args */
flags* parseargs(int argc, char** argv, char* urldest);
void showhelp();

/* url */
parsedurl* parseURL(char* fullurl);
int freeurl(parsedurl* parsed);

/* request */
char* makemessage(char* request, parsedurl* urldetails);
char* makerequest(parsedurl* urldetails);

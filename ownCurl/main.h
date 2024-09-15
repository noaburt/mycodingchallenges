
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the header file for this coding challenge

*/

/* includes & statics */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <sys/socket.h> /* for: socket, connect */
#include <netinet/in.h> /* for: struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* for: struct hostent, gethostname */

static size_t RESPONSE_SIZE = 4096;
static size_t MESSAGE_SIZE = 1024;
static long D_PORT[2] = {80, 443};

/* structs */

typedef struct FLAGS {

  /* struct to store flags enabled / disabled */

  int help;
  int verbose;
  int method;
  int data;
  int customh;

  /* string to store extra data for methods */
  char* methodstr;
  char* datastr;
  char* customhstr;
  
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
int parseargs(int argc, char** argv, flags* argflags);
char* gethelp();
int resetflags(flags* argflags);

/* url */
parsedurl* parseURL(char* fullurl);
int freeurl(parsedurl* parsed);

/* request */
char* makecontentlength(size_t length);
int showmsg(char direction, char* message);
int makemessage(char* message, parsedurl* urldetails, char* request, char* postheader, char* payload);
int makerequest(char* responsedest, parsedurl* urldetails, flags* argflags, char* message);


/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the functions file for this coding challenge

*/

#include <main.h>

const long D_PORT[2] = {80, 443};


/* flags & args */

int parseargs(int argc, char** argv, flags* argflags) {

  /* parse arguments into flag structure (already allocated space) */

  resetflags(argflags);
  
  int found = 0;
  int index = 1;

  while ( index < argc ) {

    /* if first char is '-' check for flags, else store url */
    if ( **(argv+index) == '-' ) {
      
      if ( strcmp( *(argv+index), "-h" ) == 0 || strcmp( *(argv+index), "--help" ) == 0 ) {
	argflags->help = 1;
      } else if ( strcmp( *(argv+index), "-v" ) == 0 || strcmp( *(argv+index), "--verbose" ) == 0 ) {
	argflags->verbose = 1;
      } else if ( strcmp( *(argv+index), "-X" ) == 0 || strcmp( *(argv+index), "--request" ) == 0 ) {
	argflags->method = 1;
	argflags->methodstr = *(argv+index+1);
	index++;
      } else if ( strcmp( *(argv+index), "-d" ) == 0 || strcmp( *(argv+index), "--data" ) == 0 ) {
	argflags->data = 1;
	argflags->datastr = *(argv+index+1);
	index++;
      } else if ( strcmp( *(argv+index), "-H" ) == 0 || strcmp( *(argv+index), "--header" ) == 0 ) {
	argflags->customh = 1;
	argflags->customhstr = *(argv+index+1);
	index++;
      } else {
	errx(1, "unknown argument %s", *(argv+index));
      }
      
    } else {
      found = index;
    }

    index++;
  }

  return found;
}

char* gethelp() {

  /* show usage for cccurl */
  char* help = "Usage: cccurl [options...] <url>\n"
  " -v, --vebose\t\t\tMake the operation more talkative\n"
  " -X, --request <method>\t\tSpecify request method to use\n"
  " -d, --data <data>\t\tHTTP POST data (string)\n"
  " -H, --header <header/@file>\tPass custom header to server\n"
  "\nThis is a simple version of \"curl\"\n"
  "For full curl details use \"curl --help\"";

  return help;

}

int resetflags(flags* argflags) {

  /* initialise argflags and reset values */

  argflags->help = 0;
  argflags->verbose = 0;
  argflags->method = 0;
  argflags->data = 0;
  argflags->customh = 0;
  
  argflags->methodstr = malloc( sizeof( char* ) );
  argflags->methodstr = '\0';
  argflags->datastr = malloc( sizeof( char* ) );
  argflags->datastr = '\0';
  argflags->customhstr = malloc( sizeof( char* ) );
  argflags->customhstr = '\0';

  return 0;
}

int freeflags(flags* argflags) {

  /* free space allocated from argflags */

  free(argflags->methodstr);
  free(argflags->datastr);
  free(argflags->customhstr);
  free(argflags);

  return 0;
}


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
  
  char* hostptr = parsed->host;
  
  char* portstr = malloc( sizeof( char* ) );
  char* portptr = portstr;
  
  int storeto = 0; /* 0 - reading host, 1 - reading port */
  
  while ( *urlptr != '/' ) {

    if ( *urlptr == ':') {
      *hostptr = '\0';
      storeto = 1;
      urlptr++;
    }

    if ( storeto == 0 ) {
      *hostptr = *urlptr;
      hostptr++;
    } else {
      *portptr = *urlptr;
      portptr++;
    }
    
    urlptr++;
    
  }

  *portptr = '\0';

  
  /* convert port to long and store */
  /* if port is not specified, set to default for selected protocol */
  if ( *portstr == '\0' ) {
    parsed->port = D_PORT[ parsed->protocol ];
  } else {
    parsed->port = strtol( portstr, '\0', 10 );
  }
  
  
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


/* request */

int makemessage(char* message, char* request, parsedurl* urldetails, char* postheader) {

  /* return a request message based on parsed url */

  char thisrequest[64];
  char thisheader[64];

  /* detault method is GET */
  if ( request == NULL ) {
    strcpy(thisrequest, "GET");
  } else {
    strcpy(thisrequest, request);
  }

  /* add extra headers if present */
  if ( postheader == NULL ) {
    strcpy(thisheader, "\r\n");
  } else {
    strcpy(thisheader, postheader);
  }

  char msgformat[128] = "%s %s %s/1.1\r\nHost: %s\r\nAccept: */*%sConnection: close\r\n\r\n";
  
  sprintf(message, msgformat,
	  thisrequest,
	  urldetails->path,
	  urldetails->protocol ? "HTTPS" : "HTTP",
	  urldetails->host,
	  thisheader
	  );
  
  return 0;
}

int makerequest(char* responsedest, parsedurl* urldetails, flags* argflags, char* message) {

  /* make http(s) message, request and store response in responsedest */

  /* variables from sys/socket.h, netinet/in.h, and netdb.h */
  struct hostent* server;
  struct sockaddr_in serveraddr;

  /* create the socket */
  int sockres = socket(AF_INET, SOCK_STREAM, 0);
  if (sockres < 0) {
    errx(1, "error opening socket");
  }

  /* find server */
  server = gethostbyname( urldetails->host );
  if (server == NULL) {
    errx(1, "no such host");
  }

  /* store data in struct */
  memset( &serveraddr, 0, sizeof(serveraddr) );
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons( urldetails->port );
  memcpy( &serveraddr.sin_addr.s_addr, server->h_addr, server->h_length );

  /* connect the socket */
  if ( connect(sockres, (struct sockaddr*) &serveraddr, sizeof( serveraddr ) ) < 0 ) {
    errx(1, "error connecting socket");
  }
  
  /* send request message */
  int total = strlen(message);
  int sent = 0;
  int bytes;
  
  while (sent <= total) {
      bytes = write(sockres, message+sent, total-sent);

      if (bytes < 0) {
	errx(1, "error sending request");
      }
      
      if (bytes == 0) {
	break;
      }
      
      sent+=bytes;
  }

  /* receive response */
  memset( responsedest, 0, RESPONSE_SIZE );
  total = RESPONSE_SIZE - 1;
  int received = 0;
  
  while (received <= total) {
      bytes = read(sockres, responsedest+received, total-received);
      if (bytes < 0) {
	errx(1, "error reading responsedest");
      }
      
      if (bytes == 0) {
	break;
      }
      
      received+=bytes;
  }

  //free(message);

  /* check if response string is full*/
  if (received == total) {
    errx(1, "couldn't store socket response");
  }

  /* close the socket */
  close(sockres);

  return 0;
}

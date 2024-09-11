
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the functions file for this coding challenge

*/

#include <main.h>

const long D_PORT[2] = {80, 443};


/* help */

void showhelp() {

  /* show usage for cccurl */
  printf("Usage: cccurl <url>\n\nThis is a simple version of \"curl\"\nFor full curl details use \"curl --help\"\n");

  exit(0);
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

char* makemessage(char* request, parsedurl* urldetails) {

  /* return a request message based on parsed url */

  char* message = malloc(1024);
  
  char* msgformat = "%s %s %s/1.1\r\nHost: %s\r\nAccept: */*\r\nConnection: close\r\n\r\n";

  sprintf(message, msgformat,
	  request,
	  urldetails->path,
	  urldetails->protocol ? "HTTPS" : "HTTP",
	  urldetails->host
	  );

  return message;
}

char* makerequest(parsedurl* urldetails) {

  /* make http(s) message, request and store response */

  /* create message for request, and malloc response */
  char* message = makemessage( "GET", urldetails );
  char response[4096];

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
  memset( response, 0, sizeof(response) );
  total = sizeof( response ) - 1;
  int received = 0;
  
  while (received <= total) {
      bytes = read(sockres, response+received, total-received);
      if (bytes < 0) {
	errx(1, "error reading response");
      }
      
      if (bytes == 0) {
	break;
      }
      
      received+=bytes;
  }

  /* check if response string is full*/
  if (received == total) {
    errx(1, "couldn't store socket response");
  }

  /* close the socket */
  close(sockres);
  free(message);

  char* responseptr = response;
  return responseptr;

}

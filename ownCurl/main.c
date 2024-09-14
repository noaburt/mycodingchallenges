
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is my solution for the Build Your Own curl coding challenge
found at - https://codingchallenges.fyi/challenges/challenge-curl

Development Notes:

    - Curl clone that can connect to a server and send GET, DELETE, POST, and PUT HTTP methods
    - Refer to RFC that defines HTTP, focus on HTTP 1.1 defined in https://datatracker.ietf.org/doc/html/rfc9110
    - Connection will close after every HTTP request (Connection: close)
    - Response is assumed short, space for 4096 chars

*/

#include <main.h>

int main(int argc, char** argv) {

  /* good luck */

  /* argument validation */
  int urlindex = 0;
  flags* argflags = malloc( sizeof( flags* ) );
  
  urlindex = parseargs(argc, argv, argflags);
  
  if ( argflags->help ) {
    printf("%s\n", gethelp());
    return 0;
  }

  if ( urlindex < 1 ) {
    errx(1, "no url provided");
  }
  
  /* parse url input and display request message if verbose */
  parsedurl* urldetails = parseURL( argv[urlindex] );
  char* message = makemessage( argflags->methodstr, urldetails, argflags->customhstr);
  
  if ( argflags->verbose ) {
    char* msgptr = message;
    printf("> ");
    
    while( *msgptr != '\0' ) {
      printf("%c", *msgptr);

      if ( *msgptr == '\n' && *(msgptr+1) != '\0' ) {
	printf("> ");
      }
      
      msgptr++;
    }

  }

  /* send server request and collect response */
  char* response = makerequest( urldetails, argflags, message );

  /* show response, only display headers unless verbose */
  int headerstarted = 0;
  char* responseptr = response;

  if ( argflags->verbose ) { printf("< "); }

  while( *responseptr != '\0' ) {

    if ( *responseptr == '{' ) { headerstarted = 1; }
    
    if ( headerstarted || argflags->verbose ) {
      printf("%c", *responseptr);

      if ( headerstarted == 0 ) {
	if ( *responseptr == '\n' && *(responseptr+1) != '{') {
	  printf("< ");
	}
      }
    }
      
    responseptr++;
  }

  //freeurl(urldetails);
  //freeflags(argflags);
  
  return 0;
}


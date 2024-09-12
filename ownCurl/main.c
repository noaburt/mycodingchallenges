
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
  
  /* parse url input and display request if verbose */
  parsedurl* urldetails = parseURL( argv[urlindex] );
  
  if ( argflags->verbose ) {
    showmsg( '>', makemessage("GET", urldetails) );
  }

  /* send server request and collect response */
  char* response = makerequest( urldetails );
  char* headers = splitheader( response );

  printf("%s\n", headers);

  if ( argflags->verbose ) {
    showmsg( '<', response );
  }

  freeurl(urldetails);
  
  return 0;
}


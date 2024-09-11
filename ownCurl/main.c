
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
  char* argurl = malloc( sizeof( char* ) );
  flags* argflags = parseargs(argc, argv, argurl);  

  if (argflags->help == 1) {
    showhelp();
    return 0;
  }
  
  /* parse url input and display request */
  parsedurl* urldetails = parseURL( argurl );
  printf("Sending request %s", makemessage( "GET", urldetails ));

  /* send server request and collect response */
  char* response = makerequest( urldetails );

  printf("%s\n", response);  
  
  return 0;
}


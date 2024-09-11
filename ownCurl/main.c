
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is my solution for the Build Your Own curl coding challenge
found at - https://codingchallenges.fyi/challenges/challenge-curl

Development Notes:

    - Curl clone that can connect to a server and send GET, DELETE, POST, and PUT HTTP methods
    - Refer to RFC that defines HTTP, focus on HTTP 1.1 defined in https://datatracker.ietf.org/doc/html/rfc9110
    - 

*/

#include <main.h>

int main(int argc, char** argv) {

  /* good luck */

  //printf("%s\n", *(argv+1) );
  
  parsedurl* urldetails = parseURL( *(argv+1) );

  printf("connecting to %s\nSending request GET %s %s/1.1\nHost: %s\nAccept */*\n",
	 urldetails->host, urldetails->path, urldetails->protocol ? "HTTPS" : "HTTP", urldetails->host);
  
  return 0;
}


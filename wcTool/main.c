
/*

Coding Challenges | John Crickett

Name: Noa Burt
Date: 22/08/2024

This is my solution for the Build Your Own wc Tool coding challenge
found at - https://codingchallenges.fyi/challenges/challenge-wc

Development Notes:

  THIS PROGRAM ASSUMES LAST ARGUMENT IS FILE PATH
  argc is number of arguments passed, argv is array of arguments as strings
  output is result of process followed by the file given
  -c outputs number of bytes in a file
  -l outputs number of lines

*/

#include <main.h>

int main(int argc, char** argv) {

  /* Where the magic happens */
  
  int command = parsearguments(argc, argv);

  switch(command) {

  case 0:
    /* Not a valid command */
    fprintf(stderr, "Error: No arguments provided\n");
    break;

  case 1:
    /* display number of bytes in file */
    displayresult( getbytecount( argv[argc-1] ), argv[argc-1] );
    
    break;

  case 2:
    /* display number of lines in file */
    displayresult( getlinecount( argv[argc-1] ), argv[argc-1] );
       
    break;
    
  }

  /* basic error catching for arguments */

  return 0;
}

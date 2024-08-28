
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 22/08/2024

This is my solution for the Build Your Own wc Tool coding challenge
found at - https://codingchallenges.fyi/challenges/challenge-wc

Development Notes:

  THIS PROGRAM ASSUMES LAST ARGUMENT IS FILE PATH
  argc is number of arguments passed, argv is array of arguments as strings
  output is result of process followed by the file given
  -c outputs number of bytes in a file
  -l outputs number of lines
  -w outputs number of words
  
  when lines are read from file, string terminator is \n, reading past results in seg fault
  what makes a word?????
  a word is preceded by a space or non letter character, and ended by the same
  words of length 1 to be discounted????? (with wordlength > 2 to account for wordlength just added)
  include numbers???? (with isalnum)
  

*/

#include <main.h>

int main(int argc, char** argv) {

  /* Where the magic happens */
  
  int command = parsearguments(argc, argv);

  switch(command) {

  case -1:
    /* Not a valid command */
    fprintf(stderr, "Error: No arguments provided\n");
    break;

  case 0:
    /* show help */
    printhelp();
    break;

  case 1:
    /* display number of bytes in file */
    displayresult( getbytecount( argv[argc-1] ), argv[argc-1] );
    
    break;

  case 2:
    /* display number of lines in file */
    displayresult( getlinecount( argv[argc-1] ), argv[argc-1] );
       
    break;

  case 3:
    /* display number of words in file */
    displayresult( getwordcount( argv[argc-1] ), argv[argc-1] );
    break;
    
  }

  return 0;
}

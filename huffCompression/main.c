
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 16/09/2024

This is my solution for the Build Your Own Compression Tool coding challenge
found at - https://codingchallenges.fyi/challenges/challenge-huffman

Development Notes:

*/

#include <main.h>

int main(int argc, char** argv) {

  /* good luck */

  /* parse flags and show help */
  flagstruct* parsedflags = parseflags(argc, argv);

  if ( parsedflags->help ) {
    printf("%s\n", gethelp());
    return 0;
  }

  printf("-- %d\n", parsedflags->fileindex);

  if ( freeflags(parsedflags) > 0 ) { errx(1, "flag pointer null before intended"); }

  return 0;
}


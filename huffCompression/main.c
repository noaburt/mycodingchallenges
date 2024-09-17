
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

  /* file validation */
  FILE* fileptr = fopen( *(argv+parsedflags->fileindex), "r" );

  if ( !fileptr ) {
    errx(1, "cannot read '%s': No such file or directory", *(argv+parsedflags->fileindex));
  }

  /* count characters in file */
  charcount* listhead = malloc( sizeof( charcount* ) );

  countfile(fileptr, listhead);

  charcount* countptr = listhead;
  
  while( countptr->character ) {
    
    printf("%c: %ld\n", countptr->character, countptr->count);
    
    countptr = countptr->next;
  }

  /* free structs, close file, and exit */
  fclose(fileptr);
  
  if ( freeflags(parsedflags) > 0 ) { errx(1, "flag pointer null before intended"); }
  if ( freecount(listhead) > 0 ) { errx(1, "char count pointer null before intended"); }

  return 0;
}


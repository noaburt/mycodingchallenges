
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 16/09/2024

This is the functions file for this coding challenge

*/

#include <main.h>


/* functions */

/* args */

flagstruct* parseflags(int argc, char** argv) {

  /* parse arguments and return flag struct containing flag data */

  flagstruct* parsedflags = malloc( sizeof( flagstruct* ) );

  if ( resetflags(parsedflags) > 0 ) { errx(1, "flag pointer null before indended"); }

  /* start index at 1 as argv[0] is always source (i.e. command called) */
  for( int currentindex = 1; currentindex < argc; currentindex++ ) {

    if ( **(argv+currentindex) == '-' ) {

      /* parse options */
      if ( strcmp( *(argv+currentindex), "-h" ) == 0 || strcmp( *(argv+currentindex), "--help" ) == 0 ) {
	parsedflags->help = 1;
      } else {
	errx(1, "unknown argument %s", *(argv+currentindex));
      }
      
    } else {
      parsedflags->fileindex = currentindex;
    }
    
  }

  return parsedflags;
}

int resetflags(flagstruct* flags) {

  /* reset and initialise all params of flagstruct */

  if ( !flags ) { return 1; }

  flags->help = 0;
  flags->fileindex = 0;

  return 0;
}

int freeflags(flagstruct* flags) {

  /* free allocated space for flag struct */

  if ( !flags ) { return 1; }

  free(flags);

  return 0;
}

char* gethelp() {

  /* returns string containing help and usage */

  char* helpstr = "Usage: huff [options...] <file>\n";

  return helpstr;
}


/* counting chars */

int addchar(charcount* head, char newchar) {

  /* add new char to end of linked list */

  charcount* headptr = head;

  /* find end of list */
  while( headptr->next ) {
    headptr = headptr->next;
  }

  headptr->character = newchar;
  headptr->count = 1;
  headptr->next = malloc( sizeof( charcount ) );

  return 0;
}

int countchar(charcount* head, char tocount) {

  /* increase the character count of 'tocount' by one */

  charcount* countptr = head;

  /* find character to count */
  while( countptr->next ) {
    
    if (countptr->character == tocount) {
      countptr->count++;
      return 0;
    }
    
    countptr = countptr->next;
  }

  /* character hasn't been found, add new character */
  addchar(countptr, tocount);

  return 0;
}

int countfile(FILE* fileptr, charcount* listhead) {

  /* count the occurences of each character in a file, and store in linked list */

  char currentchar;

  while(1) {
    currentchar = fgetc(fileptr);
    if (currentchar == EOF) { break; }
    countchar(listhead, currentchar);
  }

  return 0;
}

int freecount(charcount* head) {

  /* free all counts in linked list */

  if ( !head ) { return 1; }

  charcount* currentcount = head;
  charcount* prevcount;

  while( currentcount->next ) {
    prevcount = currentcount;
    currentcount = currentcount->next;
    free(prevcount);
  }

  return 0;
}


/* binary tree */

charcount* sortcounts(charcount* unsorted) {

  /* return a sorted linked list of character counts for use in binary tree */

  return NULL;
  
}

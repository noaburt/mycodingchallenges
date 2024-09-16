
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 16/09/2024

This is the header file for this coding challenge

*/

/* includes & structs */

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

typedef struct FLAGSTRUCT {

  /* struct to store parsed argument flag data */

  short int help;

  /* index of argv that file is stored */
  int fileindex;
  
} flagstruct;

typedef struct CHARCOUNT {

  /* linked list to store character count for file */

  struct CHARCOUNT* next;

  char character;
  int count;
  
} charcount;


/* functions */

/* args */
flagstruct* parseflags(int argc, char** argv);
int resetflags(flagstruct* flags);
int freeflags(flagstruct* flags);
char* gethelp();

/* counting chars */
int addchar(charcount* head, char newchar);
int freecount(charcount* head);

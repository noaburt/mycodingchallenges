
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 22/08/2024

This is the header file for this coding challenge

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* functions */

int displayresult(int count, char* filepath);
int parsearguments(int argc, char** argv);

long getbytecount(char* filepath);
long getlinecount(char* filepath);
long getwordcount(char* filepath);

int wordsinline(char* line);

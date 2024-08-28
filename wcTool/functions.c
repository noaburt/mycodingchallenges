
/*

Coding Challenges | John Crickett

Name: Noa Burt
Date: 22/08/2024

This is the functions file for this coding challenge

*/

#include <main.h>


int displayresult(int count, char* filepath) {

  /* display result given to stdout */
  
  if ( count <= 0 ) {
    return -1;
  }

  fprintf(stdout, "\n%d %s\n", count, filepath);

  return 0;
}

int parsearguments(int argc, char** argv) {

  /* return a number based on the arguments passed */

  /*
    return values:

    0: invalid parameters
    1: -c number of bytes
    2: -l number of lines
    
   */

  while ( *(argv) != NULL) {

    if ( *( *(argv) ) == '-' ) {
      //printf("\n --- %c --- ", *(*(argv)+1) );

      if ( *( *(argv)+1 ) == 'c' ) {
	return 1;
      }

      if ( *( *(argv)+1 ) == 'l' ) {
	return 2;
      }
      
    }
    
    argv++;
  }

  return 0;
}


long getbytecount(char* filepath) {

  /* count bytes in file filepath and return */
  FILE* fileptr;
  long filelen;

  /* open file in binary read mode, jump to end of file, and read byte offset */
  fileptr = fopen(filepath, "rb");

  if ( !fileptr ) {
    /* no file found error */
    perror("Error opening file");
    return -1;
  }
  
  fseek(fileptr, 0L, SEEK_END);
  filelen = ftell(fileptr);

  if (filelen == -1L) {
    /* ftell failed */
    perror("Error finding end of file");
    return -1;
  }

  fclose(fileptr);

  return filelen;
}

long getlinecount(char* filepath) {

  /* count lines in file filepath and return */
  FILE* fileptr;
  long linecount;

  /* open file in normal read mode, read lines until end is reached */
  fileptr = fopen(filepath, "r");

  if ( !fileptr ) {
    /* no file found error */
    perror("Error opening file");
    return -1;
  }

  char* line = malloc(100);
  
  while( fgets(line, 99, fileptr) ) {
    linecount++;
  }

  free(line);    
  fclose(fileptr);  

  return linecount;
}
























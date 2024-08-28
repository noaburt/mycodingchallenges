
/*

Coding Challenges | John Crickett

Author: Noa Burt
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
    3: -w number of words
    
   */

  while ( *(argv) != NULL) {

    if ( *( *(argv) ) == '-' ) {
      //printf("\n --- %c --- ", *(*(argv)+1) );
      char flag = *( *(argv)+1 );

      if ( flag == 'c' ) {
	return 1;
      }

      if ( flag == 'l' ) {
	return 2;
      }

      if ( flag == 'w' ) {
	return 3;
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

long getwordcount(char* filepath) {

  /* count words in file filepath and return */

  FILE* fileptr;
  long wordcount;

  /* open file in normal read mode, read each line into buffer, count words, until end is reached */
  fileptr = fopen(filepath, "r");

  if ( !fileptr ) {
    /* no file found error */
    perror("Error opening file");
    return -1;
  }

  char* line = malloc(256);
  
  while( fgets(line, 256, fileptr) ) {
    wordcount += wordsinline(line);
  }

  free(line);    
  fclose(fileptr);  

  return wordcount;
}


int wordsinline(char* line) {

  /* count spaces in line (including end of line) and return */

  char* lineptr = line;
  int spacecount = 0;
  int wordlength = 0;

  while (lineptr) {

    if ( *lineptr == '\n' ) {

      /* end of line has been reached */

      if ( wordlength >= 1 ) {
	spacecount++;
      }

      break;
      
    }
    
    if ( wordlength == 0 ) {

      /* a word has not begun */

      if ( isalnum( *lineptr ) ) {
	wordlength = 1;
      }
      
    } else {

      /* a word has begun already */
      wordlength++;

      if ( !isalnum( *lineptr ) ) {

	if (wordlength > 2) {
	  /* word length bigger than 1 (including 1 just added above) */
	  spacecount++;
	}
	wordlength = 0;
      }
      
    }

    lineptr++;
    
  }

  return spacecount;
}

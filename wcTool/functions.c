
/*

Coding Challenges | John Crickett

Author: Noa Burt
Date: 22/08/2024

This is the functions file for this coding challenge

*/

#include <main.h>


void printhelp() {

  /* print instructions of use for the user */

  char* helpmessage =
    "Usage: ./main [OPTION]... [FILE]...\nPrint newline, word, and byte counts for a FILE. A word is a\nnon-zero-length sequence of printable characters delimited\nby white space.\n\nThe options below may be used to select which counts are printed.\n  -c\t\t\tprint the byte count\n  -l\t\t\tprint the newline count\n  -w\t\t\tprint the word count\n\n  --help\t\tdisplay this help and exit";

  fprintf(stdout, "%s\n", helpmessage);
  
}

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

    if ( strcmp( *argv, "--help" ) == 0 ) {
      return 0;
    }

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

  return -1;
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
  /* a word is a non-zero-length sequ. of printable chars delimited by white space */

  char* lineptr = line;
  int wordcount = 0;
  int wordlength = 0;

  while (lineptr) {

    if ( *lineptr == '\n' ) {
      /* signifies end of the line */
      
      if ( wordlength > 0 ) {
	wordcount++;
      }

      return wordcount;
    }

    if ( isprint( *lineptr ) ) {
      /* printable character, if it is a space, check word length */

      if ( *lineptr == ' ' ) {
	if ( wordlength > 0 ) { wordcount++; }
      } else {
	wordlength++;
      }
      
    } else {
      /* non printable, reset word length */
      
      wordlength = 0;
    }

    lineptr++;
    
  }

  return -1;
}

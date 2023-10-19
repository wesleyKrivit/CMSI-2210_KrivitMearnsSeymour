/*
 *  file: duplicitous.c
 *  practice with File I/O by doing the following:
 *
 *    read the command line arguments
 *    if none are present, output a usage message of how to run the
 *       program next time
 *    also if none are present, ask the user for a file name
 *    also if none are present, ask the user for an integer between 1 and 10
 *       this will be used for the number of times to copy file contents
 *    regardless of input method, set the filename into a variable called
 *       'filename'
 *    also regardless of input method, set the integer into a variable
 *       called "copies"
 *    try to open the input file and report any errors that occur
 *    if the file opens OK, read the first line from the file
 *    convert the number on the line from a string to an int; this is the
 *       count of lines to be copied to the output file ~ call this 'count'
 *    display a message: file %s is open will copy %d lines
 *    now create an output file name, using the name output.txt
 *    open the output file and report any errors that occur
 *    read each line of the input file, writing it to the output file
 *    when count lines have been written to the output, write a newline
 *       to the output file
 *    call the rewind() function to move the input file pointer back to the
 *       start of the input file JUST AFTER the first line
 *    read each line of the input file again, writing it to the output file
 *    repeat steps 14, 15, and 16 for copies times
 *    close both files
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

/*
 * helper method to output instructions for the user for next time
 */
void instructions() {
    printf( "\n\n   This is a file copier program.\n" );
    printf( "   It copies a block of text multiple times to an output file.\n" );
    printf( "   The input file name should be given as an argument.\n" );
    printf( "   If one is not provided, you will be asked for it.\n" );
    printf( "   You must also enter a number of times to copy the text block.\n" );
    printf( "   The number must be an integer value 1 through 10 inclusive.\n" );
    printf( "   If a number is not provided, you will be asked for it.\n" );
    printf( "\n\n" );
}

void appendNewline(char* str){
   if (str[strlen(str) - 1] != '\n'){
      strcat(str, "\n");
   }
}

const size_t MAX_ARRAY_LENGTH = 1000;
const int MIN_COPIES = 1;
const int MAX_COPIES = 10;

/*
 * main method
 *    entry point
 *    "Speak friend and enter"
 */ 
int main( int argc, char * argv[] ) {

   char filename[250];
   char copyLine[10];

   int blocksize = 0;
   int copyCount = 0;

   if( argc < 3 ) {
      instructions();
      printf( "   Enter a file name: " );
      fflush( stdout );
      scanf( "%s", filename );
      fflush( stdout );
      do {
      printf( "   Enter a number from %d through %d: ", MIN_COPIES, MAX_COPIES);
      fflush( stdin );
      scanf( "%d", &copyCount );
      } while (copyCount < MIN_COPIES || copyCount > MAX_COPIES);
   } else {
      strcpy( filename, argv[1] );
      copyCount = atoi( argv[2] );
      fflush( stdout );
   }
   printf( "     ...proceeding with file copy on file %s.\n", filename );
   printf( "     ...copying file block %d times.\n", copyCount );

  /*
   * open the input file and check open error
   */
   FILE* in = fopen(filename, "r");
   if (!in){
       printf("   Error opening %s, the input file!\n", filename);
       return 1;
   }
  /*
   * read the first line of the input file to get the readline count
   */
   char line[MAX_ARRAY_LENGTH];
   fgets(line, MAX_ARRAY_LENGTH, in);
   long long first_line_end = strlen(line) + 1; // skip the newline
   int num_lines = atoi(line);
   if (num_lines == 0){
       printf("Invalid line count found!\n");
       return 2;
   }
   printf("File %s will copy %d lines...\n", filename, num_lines);
  /*
   * open the output file and check open error
   */
   FILE* out = fopen("output.txt", "w");
   if (!out){
       printf("   Error opening the output file!\n");
       return 3;
   }
  /*
   * read that many lines from the input file and
   *  write them to the output file
   */
   if (num_lines > 0){
      for (int i = 0; i < copyCount; i++){
         int line_count = 0;
         if (fgets(line, MAX_ARRAY_LENGTH, in) == NULL) break;
         while (line_count < num_lines) {
            appendNewline(line);
            fwrite(line, sizeof(char), strlen(line), out);
            if (fgets(line, MAX_ARRAY_LENGTH, in) == NULL) break;
               line_count++;
            }
            fseek(in, first_line_end, SEEK_SET);
         }   
   }
   else{
      size_t total_lines = 0;
      while (fgets(line, MAX_ARRAY_LENGTH, in) != NULL){
         total_lines++;
      }
	   
      num_lines *= -1;
      if (total_lines < num_lines){
         num_lines = total_lines;
      }
      for (int i = 0; i < copyCount; i++){
         fseek(in, first_line_end, SEEK_SET);
         int line_count = 0;
         while (line_count < total_lines) {
            fgets(line, MAX_ARRAY_LENGTH, in);
            appendNewline(line);
            if (line_count >= total_lines - num_lines){
               fwrite(line, sizeof(char), strlen(line), out);
            }
            line_count++;
         }
      }   
   }
   
  /*
   * clean up after yourself
   */
   fclose( in );
   fclose( out );

   exit( 0 );
}

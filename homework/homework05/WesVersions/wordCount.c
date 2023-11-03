#include "stdio.h"


#include "ctype.h"

int main(int argc, char *argv[])
{
    // opens file at given path
    const char *fileToRead = argv[1];
    FILE *in = fopen(fileToRead, "r");

    // if incorrect number of command line arguments or file error, stops program
    if (argc != 2 || !in)
    {
        printf("ERROR!!!!");
        return 0;
    }

    int wordCount = 0;

    // scans through file until error code meaning end has been reached
    while (fscanf(in, "%*s") != -1)
        wordCount++;
        
    printf("file has %d words!", wordCount);
    fclose(in);
  
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){-
    printf("function start \n");
    int decNum = atoi(argv[0]);
    
    //the byteSize is 32 by default, only the optional 64 byte command will change it to 64
    int byteSize = 32;
	if (argc > 1 & atoi(argv[2]) == 64) {
	   byteSize = 64;
	} 
    
    //divided to work with the number of digits in the hex string that will be returned
    byteSize/=4;
    
    //used to easily map any hex values greater than 9 to the correct character
    char hexTranslation[] = {'A','B','C','D','E','F'};
    
    //creates memory space for a char array that holds the binary string, and sets the first two
    //digits to the hexcode 0x
    char* hexNum = malloc (byteSize *sizeof(char));
    hexNum[0] = '0';
    hexNum[1] = 'x';
    
    
    //the integer digit that will be updated as the remainder for the hex conversion
    int currentDigit = 0;
    
    //for loop that goes backwards so the modulus decimal to hex technique can work
    //bytesize +1 is bytesize-1 for the loop but plus 2 because of the 0x that need to 
    //go at the beginning, the ending boundary for i is also adjusted simmilarly
    for(int i = (byteSize+1); i > 1;i--){
        currentDigit = decNum % 16;
        decNum /= 16;
        //if the number is 0-9 it can be kept as an int and converted like normal
        if(currentDigit < 10)
            //shorthand for converting an int to a char using its index
            hexNum[i] = currentDigit+'0';
        //if it is A-F, it is put through the translation Array to the correct char    
        else{
            hexNum[i] = hexTranslation[currentDigit-10];
        }
    }
    printf("\nhex number is: \n");
    printf(hexNum);
    return 0;
}

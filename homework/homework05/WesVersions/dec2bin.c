#include <stdio.h>
#include <stdlib.h>

int main(char *argv[]) {
    printf("function start \n");
    int decNum = atoi(argv[1]);
    
    //creates memory space for a char array that holds the binary string
    char* binNum = malloc (32 *sizeof(char));
    
    //the integer digit that will be updated as the remainder for the binary conversion
    int currentDigit = 9;
    
    //for loop that goes backwards so the modulus decimal to binary technique can work
    for(int i = 31; i > -1;i--){
        currentDigit = decNum % 2;
        decNum /= 2;
        //shorthand for converting an int to a char using its index
        binNum[i] = currentDigit+'0';
    }
    printf("\n binary number is: \n");
    printf(binNum);
    return 0;
}

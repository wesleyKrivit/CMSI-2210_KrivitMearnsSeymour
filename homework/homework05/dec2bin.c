#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char** argv){
	const short EXPECTED_ARGS = 2;
	const int NUMBER_OF_BITS = 32;
	const long long MAX_32_BIT_NUMBER = 4294967295;
	char* MAX_32_BIT_STRING;
	sprintf(MAX_32_BIT_STRING, "%llu", MAX_32_BIT_NUMBER);
	
	if (argc < EXPECTED_ARGS){
		printf("Less arguments passed than expected!\n");
		return 1;
	}
	if (argc > EXPECTED_ARGS){
		printf("More arguments passed than expected!\n");
		return 2;
	}
	unsigned long long decimal = strtoul(argv[1], NULL, 10);
	if (decimal > MAX_32_BIT_NUMBER ||
		(decimal == 0 && strcmp(argv[1], "0")) || 
		(decimal == -1 && strcmp(argv[1], MAX_32_BIT_STRING))){
		printf("Argument too large for %d bits (or it's just not a number)!\n", NUMBER_OF_BITS);
		return 3;
	}
	else{
		char* bits = calloc(sizeof(char), NUMBER_OF_BITS + 1);
		for (int i = NUMBER_OF_BITS - 1; i >= 0; i--){
			short bit = decimal % 2;
			decimal = decimal >> 1;
			bits[i] = bit + '0';
		}
		printf("%s\n", bits);
	}
	
	return 0;
}
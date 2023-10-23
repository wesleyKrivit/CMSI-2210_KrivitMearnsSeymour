#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char** argv){
	const short MIN_ARGS = 2;
	const short MAX_ARGS = 3;
	const int NUMBER_OF_BITS[] = {32, 64};
	const int BITS_IN_NYBBLE = 4;
	const int HEX_BASE = 16;
	const int NUMBER_OF_DIGITS[] = {(NUMBER_OF_BITS[0] / BITS_IN_NYBBLE), (NUMBER_OF_BITS[1] / BITS_IN_NYBBLE)};
	const unsigned long long MAX_NUMBER[] = {4294967295, 18446744073709551615};
	char MAX_STRING[2][100];
	
	sprintf(MAX_STRING[0], "%llu", MAX_NUMBER[0]);
	sprintf(MAX_STRING[1], "%llu", MAX_NUMBER[1]);
	
	if (argc < MIN_ARGS){
		printf("Less arguments passed than expected!\n");
		return 1;
	}
	if (argc > MAX_ARGS){
		printf("More arguments passed than expected!\n");
		return 2;
	}

	int use_64_bit = 0;
	if (argc == 3){
		// would've used a switch for this but gcc wasn't a fan of it
		int bit_arg = atoi(argv[2]);
		if (bit_arg == NUMBER_OF_BITS[0]) use_64_bit = 0;
		else if (bit_arg == NUMBER_OF_BITS[1]) use_64_bit = 1;
		else printf("Invalid number of bits (defaulting to %u)\n", NUMBER_OF_BITS[use_64_bit]);
	}
	
	unsigned long long decimal = strtoull(argv[1], NULL, 10);
	if (decimal > MAX_NUMBER[use_64_bit] ||
		(decimal == 0 && strcmp(argv[1], "0")) || 
		(decimal == -1 && strcmp(argv[1], MAX_STRING[use_64_bit]))){
		printf("Argument too large for %d bits (or it's just not a number)!\n", NUMBER_OF_BITS[use_64_bit]);
		return 3;
	}
	else{
		char* bits = calloc(sizeof(char), NUMBER_OF_BITS[use_64_bit] + 1);
		for (int i = NUMBER_OF_BITS[use_64_bit] - 1; i >= 0; i--){
			short bit = decimal % 2;
			decimal = decimal >> 1;
			bits[i] = bit + '0';
		}
		printf("%s\n", bits);
	}
	
	return 0;
}
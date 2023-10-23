#include "stdio.h"
#include "ctype.h"

int main(int argc, char** argv){
	const int EXPECTED_ARGS = 2;
	if (argc < EXPECTED_ARGS){
		printf("Insufficient arguments presented! Service refused!\n");
		return 1;
	}
	else if (argc > EXPECTED_ARGS){
		printf("Unacceptable argument surplus detected! All activity halted!\n");
		return 2;
	}
	
	const char* filename = argv[1];
	FILE* in = fopen(filename, "r");
	if (!in){
		printf("No file found at %s! Is your path and/or spelling correct?\n");
		return 3;
	}
	
	printf("Scanning document... ");
	unsigned long long word_count = 0;
	while(fscanf(in, "%*s") != -1){
		word_count++;
	}
	printf("It seems your file has %llu words!\n", word_count);
	
	fclose(in);
	
	return 0;
}

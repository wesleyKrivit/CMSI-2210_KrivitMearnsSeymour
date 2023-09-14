#include "stdio.h"
#include "string.h"
#include "stdbool.h"

bool isAlpha(char* str, int len){
	for(int i = 0; i < len - 1; i++){
		if (!((str[i] >= 'A' && str[i] <= 'z') || str[i] == ' '))
			return false;
	}
	return true;
}

char* nato_phonetic [] = {
	"",
	"ALFA",
	"BRAVO",
	"CHARLIE",
	"DELTA",
	"ECHO",
	"FOXTROT",
	"GOLF",
	"HOTEL",
	"INDIA",
	"JULIETT",
	"KILO",
	"LIMA",
	"MIKE",
	"NOVEMBER",
	"OSCAR",
	"PAPA",
	"QUEBEC",
	"ROMEO",
	"SIERRA",
	"TANGO",
	"UNIFORM",
	"VICTOR",
	"WHISKEY",
	"XRAY",
	"YANKEE",
	"ZULU"
};

char input[50];

int main(void){
	printf("Care to enter a phrase? ");
	size_t input_len;
	do{
		fgets(input, sizeof(input), stdin);
		
		size_t input_len = strlen(input);
		if (input_len > 0 && input[input_len - 1] == '\n')
		input[input_len - 1] = '\0';
	
		if (!isAlpha(input, input_len))
			printf("Please enter a phrase with just letters and spaces: ");
		else
			break;
	} while (!isAlpha(input, input_len));
	
	input_len = strlen(input);
	for(int i = 0; i < input_len - 1; i++){
		char c = input[i];
		if (c >= 'a' && c <= 'z'){
			c -= 'a';
			c++; // ha
		}
			
		else if (c >= 'A' && c <= 'Z'){
			c -= 'A';
			c++; // ha but again
		}
		else if (c == ' ')
			c -= ' ';
		
		printf("%s\n", nato_phonetic[c]);
	}
	
	return 0;
}




	
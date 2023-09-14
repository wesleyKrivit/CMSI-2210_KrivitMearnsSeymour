#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

const size_t buffer_size = 50;

bool isFloat(char* str, int len){
	int period_count = 0;
	for(int i = 0; i < len - 1; i++){
		char c = str[i];
		if (c == '.' && i < len - 2)
			period_count++;
		else if (!(c >= '0' && c <= '9'))
			return false;
	}
	return (period_count <= 1);
}

bool isCurrency(char* str, int len){
	if (isFloat(str, len)){
		char* period_pointer = strchr(str, '.');
		size_t period_pos = period_pointer - str;
		if (period_pos == -1 || period_pos > buffer_size){
			return true;
		}	
		else{
			return (len - period_pos <= 4); 
		}	
	}
	return false;
}

int main(void){
	char input[buffer_size];
	printf("Enter your principal amount: $");
	size_t input_len = strlen(input);
	do{
		fgets(input, sizeof(input), stdin);
		
		input_len = strlen(input);
		if (input_len > 0 && input[input_len - 1] == '\n')
		input[input_len - 1] = '\0';
	
		if (!isCurrency(input, input_len))
			printf("Please enter a valid currency: $");
	} while (!isCurrency(input, input_len));
	
	double principal = atof(input);
	
	printf("Enter the annual interest rate as a percent: ");
	input_len = strlen(input);
	do{
		fgets(input, sizeof(input), stdin);
		
		input_len = strlen(input);
		if (input_len > 0 && input[input_len - 1] == '\n')
		input[input_len - 1] = '\0';
	
		if (!isFloat(input, input_len))
			printf("Please enter a valid currency: $");
	} while (!isFloat(input, input_len));
	
	double interest = atof(input);
}
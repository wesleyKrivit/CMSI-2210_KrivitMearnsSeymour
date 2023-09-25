#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

bool isNumber(char* input){
	if (atoi(input) != 0)
		return true;
	else{
		for (int i = 0; i < strlen(input) - 1; i++){
			if (input[i] != '0')
				return false;
		}
		return true;
	}
}

void getString(char* input, size_t length){
	fgets(input, length, stdin);
	size_t input_len = strlen(input);
	if (input_len > 0 && input[input_len - 1] == '\n')
		input[input_len - 1] = '\0';
}

const int BUFFER_SIZE = 25;
const int MAX_NUMBERS = 25;
const int END_FLAG = -9999;

int main(void){
	char input_buf[BUFFER_SIZE];
	char number_strings[BUFFER_SIZE][MAX_NUMBERS];
	int numbers[MAX_NUMBERS];
	int num_numbers = 0;
	
	while (num_numbers < MAX_NUMBERS){
		printf("Enter a number (numbers remaining: %d): ", MAX_NUMBERS - num_numbers);
		getString(input_buf, BUFFER_SIZE);
		if (!isNumber(input_buf))
			printf("\tInvalid input received.\n");
		else{
			printf("\tInput received.\n");
			int next_number = atoi(input_buf);
			if (next_number == END_FLAG){
				printf("\tInput terminated.\n");
				break;
			}
			strcpy(number_strings[num_numbers], input_buf);
			numbers[num_numbers] = next_number;
			num_numbers++;
		}
	}
	
	if (num_numbers > 0){
		long long sum = 0;
		
		for (int i = 0; i < num_numbers; i++){
			sum += numbers[i];
		}
		double average = (double)sum / (double)num_numbers;
		
		printf("Sum: %d\n", sum);
		printf("Average: %f\n", average);
		
		char* concatenation = number_strings[0];
		for(int i = 1; i < num_numbers; i++){
			strcat(concatenation, number_strings[i]);
		}
		printf("Final string: %s\n", concatenation);
		
		int num_sevens = 0;
		for (int i = 0; i < strlen(concatenation) - 1; i++){
			if (concatenation[i] == '7')
				num_sevens++;
		}
		printf("Number of sevens: %d\n", num_sevens);
	}
	else{
		printf("No numbers given. I sleep now.\n");
	}
	
	return 0;
}
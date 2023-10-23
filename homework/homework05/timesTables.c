#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void straln(char* str, size_t new_size, int left_align){
	size_t len = strlen(str);
	if (len == new_size) return;
	
	if(left_align){
		for(int i = 0; i < new_size; i++){
			if (i >= len){
				str[i] = ' ';
			}
		}
		
	}
	else{
		memmove((str + new_size - len), str, len);
		for(int i = 0; i < new_size - len; i++){
			str[i] = ' ';
		}
	}
	str[new_size + 1] = '\0';
}

int main(int argc, char** argv){
	const int EXPECTED_ARGS = 2;
	const int MIN_N_VALUE = 2;
	const int MAX_NUM_CHARACTERS = 22;
	
	if (argc < EXPECTED_ARGS){
		printf("Less arguments passed than expected!\n");
		return 1;
	}
	else if (argc > EXPECTED_ARGS){
		printf("More arguments passed than expected!\n");
		return 2;
	}
	unsigned long n = strtoull(argv[1], NULL, 10);
	if (n < MIN_N_VALUE){
		printf("Invalid value for n read!\nMake sure it's %u or greater (and a number)!\n", MIN_N_VALUE);
		return 3;
	}
	
	unsigned long long n_as_long = (unsigned long long)n;
	unsigned long long n_squared = n_as_long * n_as_long;
	char buffer[MAX_NUM_CHARACTERS];
	sprintf(buffer, "%llu", n_squared);
	int max_int_length = strlen(buffer);
	printf("%s %d\n", buffer, max_int_length);

	printf("Your times table, as requested:\n");
	for (int i = MIN_N_VALUE - 2; i <= n; i++){
		for (int j = MIN_N_VALUE - 1; j <= n; j++){
			if (i == MIN_N_VALUE - 1){
				for (int k = 0; k < max_int_length + 2; k++){
					printf("-");
				}
			}
			else {
				if (i == MIN_N_VALUE - 2){
					if (j == MIN_N_VALUE - 1){
						sprintf(buffer, " x");
					}
					else{
						sprintf(buffer, "%llu:", j);
					}
				}
				else if (j == MIN_N_VALUE - 1){
					sprintf(buffer, "%llu:", i);
				}
				else {
					sprintf(buffer, "%llu", i * j);
				}	
				straln(buffer, max_int_length, 0);
				printf(" %s ", buffer);				
			}

			if (j == MIN_N_VALUE - 1){
				printf("|");
			}
		}
		printf("\n");
	}
	return 0;
}	
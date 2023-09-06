#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main (void) {
	printf("Your name, please: ");
	char name [59];
	fgets(name, sizeof(name), stdin);
	
	size_t name_len = strlen(name);
	if (name_len > 0 && name[name_len - 1] == '\n')
		name[name_len - 1] = '\0';
	
	printf("\tGreetings, %s!", name);
	return 0;
}
// TO BUILD (ON WINDOWS)
// compile and link with: gcc paritygen.obj paritygen.c -std=c99 -o paritygen.exe (paritygen.asm must have been assembled first!)
// just compile with: gcc -c paritygen.c -std=c99
// run with: paritygen.exe

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint32_t paritygen(uint8_t);

int main(int argc, char** argv){
	uint8_t a = atoi(argv[1]);
	printf("%u\n", paritygen(a));
	return 0;
}

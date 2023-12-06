// TO BUILD (ON WINDOWS)
// compile and link with: gcc whichEndIsUp.c -std=c99 -o whichEndIsUp.exe
// just compile with: gcc -c whichEndIsUp.c -std=c99
// run with: whichEndIsUp.exe
#include <stdio.h>
#include <inttypes.h>

int main(){
	uint16_t test_num = 0x33AA;	
	void* num_ptr = &test_num;
	uint8_t* first_byte = num_ptr;
	*first_byte = 0x00;
	printf("This machine is %s-endian!\n", ((test_num < 0x100) ? "big" : "little"));
	return 0;
}

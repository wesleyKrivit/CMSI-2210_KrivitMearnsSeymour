gcc makeNBO.c -o makeNBO.exe

	
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int isBigEndian(){
	uint16_t test_num = 0x33AA;	
	void* num_ptr = &test_num;
	uint8_t* first_byte = num_ptr;
	*first_byte = 0x00;
	return (test_num < 0x100);
}

void makeNBO(void* value, size_t num_bytes){
	// nothing to swap
	if (isBigEndian() || num_bytes == 1)
		return;
	uint8_t* buffer = (uint8_t*)(calloc(num_bytes, 1));
	for(int i = 0; i < num_bytes; i++){
		*(buffer + num_bytes - 1 - i) = *(uint8_t*)(value + i);
	}
	for(int i = 0; i < num_bytes; i++){
		*(uint8_t*)(value + i) = *(buffer + i);
	}
	free(buffer);
}

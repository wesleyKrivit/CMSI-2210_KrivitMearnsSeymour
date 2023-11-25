#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

uint32_t gcdFinder(uint32_t, uint32_t);

void testGCD(uint32_t a, uint32_t b, uint32_t intended){
	printf("Testing GCD of %u and %u (should be %u)...", a, b, intended);
	uint32_t gcd = gcdFinder(a, b);
	printf("got %u...\n", gcd);
	assert(gcd == intended);
	printf("...Success!\n");
}

int main(){
	//testGCD(3113041662, 11570925, 462837);
	testGCD(69, 36, 3);
	return 0;
}
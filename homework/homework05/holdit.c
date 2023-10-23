#include "stdio.h"
#include "time.h"

int main(){
	printf("Congratulations on becoming one of the Chosen!\n");
	printf("Before you may begin your ascension,\nplease participate in a simple assessment of your vessel's capabilities.\n");
	printf("Press ENTER when you are ready.\n");
	getchar();
	printf("Take a deep breath, deeper than any you've ever taken in your physical life.\n");
	printf("Press ENTER as soon as you have.\n");
	getchar();
	clock_t start_time = clock();
	printf("Hold your breath for as long as you possibly can.\n");
	printf("Once your vessel has failed you, press ENTER immediately.\n");
	getchar();
	clock_t end_time = clock();
	double final_time = (double)(end_time - start_time) / (double)CLOCKS_PER_SEC;
	printf("It seems that you managed to hold your breath for %0.3f seconds.\n", final_time);
	printf("...\nOur judgement has lapsed.\nYour vessel is ill equipped for the new world.\n");
	printf("This session has ended - do not contact us again.\n");
	return 0;
}
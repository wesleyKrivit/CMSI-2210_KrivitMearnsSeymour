#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int msec = 0, trigger = 100000; /* 10ms */
    clock_t before = clock();

    char enterChar[2] = "";
    printf("This program will time how long you can hold your breath.\nTake a deep breath, then press the 'Enter' key.\nWhen you absolutely have to exhale, press the enter key again.\nThe duration will be displayed in minutes and seconds.");

    // checks to see if enter is pressed
    if (1 == scanf("%1[\n]", enterChar))
    {
        printf("timer started! \n");
        clock_t before = clock();

        if (1 == scanf("%1[\n]", enterChar))
        {
            clock_t difference = clock() - before;
            msec = difference / CLOCKS_PER_SEC;
            printf("Breath held for %d min and %d seconds", msec / 60, msec % 60);
            return 0;
        }
    }

    return 0;
}

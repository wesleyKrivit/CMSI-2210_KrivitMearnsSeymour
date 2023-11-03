#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Times table up to %s", argv[1]);
    int maxValue = atoi(argv[1]);

    int currentProduct = 0;

    printf("\n");
    for (int i = 1; i < maxValue + 1; i++)
    {
        for (int j = 1; j < maxValue + 1; j++)
        {
            currentProduct = j * i;
            printf("| ");
            if (currentProduct < 10)
                printf("  ");
            else if (currentProduct < 100)
                printf(" ");

            printf("%d ", currentProduct);
        }
        printf("\n");
    }

    return 0;
}

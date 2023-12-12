#include "./main.h"

int main()
{
    printf("Work is not done for the moment.\n");

    int* intValue = malloc_3is(sizeof(int));
    *intValue = 7;

    float* floatValue = malloc_3is(sizeof(float));
    *floatValue = 4.2;

    printf("Both value are: %d, %f\n", *intValue, *floatValue);

    printf("Adresses: %p, %p\n", intValue, floatValue);

    // Difference : 0x24 = 36.
    // Logical, size of int : 4, size of magic number : 8, size of HEADER : 24

    printf("%ld", sizeof(HEADER));

    return EXIT_SUCCESS;
}
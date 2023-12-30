#include "./main.h"

extern HEADER* headOfHeap;

int main()
{
    printf("Work is not finished for the moment.\n");

    float* floatValue = malloc_3is(sizeof(float));
    *floatValue = 4.2;

    int* intValue = malloc_3is(sizeof(int));
    *intValue = 7;

    printf("The values are: %d, %f\n", *intValue, *floatValue);

    printf("Adresses: %p, %p\n", intValue, floatValue);

    // Difference : 0x24 = 36.
    // Logical, size of int : 4, size of magic number : 8, size of HEADER : 24, size of long = 8, size of char = 1

    printf("Is float adress correct? %d\n", checkIfAdressCorrect(floatValue));
    free_3is(floatValue);
    printf("Is int adress correct? %d\n", checkIfAdressCorrect(intValue));
    free_3is(intValue);

    int* intValue2 = malloc_3is(sizeof(int));
    *intValue2 = 15;

    printf("Is head non-null? %d\n", (NULL != headOfHeap));
    printf("Is after head null? %d\n", (NULL == headOfHeap->ptr_next));
    printf("Is second int adress correct? %d\n", checkIfAdressCorrect(intValue2));
    free_3is(intValue2);

    printf("------------------------------\n");

    // Allocation for a List (64 o) -> Creation of a new bloc
    int* intList = malloc_3is(16*sizeof(int));
    for(int i=0;i<16;i++){intList[i] = i;}

    printf("Is int list adress correct? %d\n", checkIfAdressCorrect(intList));
    free_3is(intList);

    long* longValue = malloc_3is(sizeof(long));

    printf("Is long Value adress correct? %d\n", checkIfAdressCorrect(longValue));
    free_3is(longValue);

    return EXIT_SUCCESS;
}
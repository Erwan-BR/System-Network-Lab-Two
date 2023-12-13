#include "./main.h"

extern HEADER* headOfHeap;

int main()
{
    printf("Work is not finished for the moment.\n");

    float* floatValue = malloc_3is(sizeof(float));
    *floatValue = 4.2;

    int* intValue = malloc_3is(sizeof(int));
    *intValue = 7;

    

    printf("Both value are: %d, %f\n", *intValue, *floatValue);

    printf("Adresses: %p, %p\n", intValue, floatValue);

    // Difference : 0x24 = 36.
    // Logical, size of int : 4, size of magic number : 8, size of HEADER : 24

    printf("Is float adress correct? %d\n", checkIfAdressCorrect(floatValue));
    free_3is(floatValue);
    printf("Is int adress correct? %d\n", checkIfAdressCorrect(intValue));
    free_3is(intValue);

    assert(NULL != headOfHeap);
    assert(NULL != headOfHeap->ptr_next);
    assert(NULL == headOfHeap->ptr_next->ptr_next);

    int* intValue2 = malloc_3is(sizeof(int));
    *intValue2 = 15;

    printf("Is head non-null? %d\n", (NULL != headOfHeap));
    printf("Is after head null? %d\n", (NULL == headOfHeap->ptr_next));
    printf("Old int (re-used) and new int: %d, %d\n", *intValue, *intValue2);
    printf("Is second int adress correct?%d\n", checkIfAdressCorrect(intValue2));
    free_3is(intValue2);

    return EXIT_SUCCESS;
}
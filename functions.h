#ifndef functions_h
#define functions_h

#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 2048
#define MAGIC_NUMBER 0x0123456789ABCDEFL

typedef struct HEADER_TAG {
    struct HEADER_TAG * ptr_next;   /* Points to the next free bloc. */
    size_t bloc_size;               /* Size of the memory bloc, in BYTES. */
    long magic_number;              /* 0x0123456789ABCDEFL */
} HEADER;

void *malloc_3is(size_t size);
void free_3is(void *ptr);
bool checkIfAdressCorrect(void* ptr);
void linkBlocks(HEADER* ptr1, HEADER* ptr2);

#endif /* functions_h */
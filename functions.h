#ifndef functions_h
#define functions_h

#include <stddef.h>
#include <unistd.h>

#define BLOCK_SIZE 2048
#define MAGIC_NUMBER 0x0123456789ABCDE

typedef struct HEADER_TAG {
    struct HEADER_TAG * ptr_next;   /* Points to the next free bloc. */
    size_t bloc_size;               /* Size of the memory bloc, in BYTES. */
    long magic_number;              /* 0x0123456789ABCDE */
} HEADER;

void *malloc_3is(size_t size);
void free_3is(void *ptr);

#endif /* functions_h */
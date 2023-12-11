#ifndef functions_h
#define functions_h

#include <stddef.h>

typedef struct HEADER_TAG {
    struct HEADER_TAG * ptr_next;   /* Points to the next free bloc. */
    size_t bloc_size;               /* Size of the memory bloc, in BYTES. */
    long magic_number;              /* 0x0123456789ABCDEFL */
} HEADER;

#endif /* functions_h */
#include "./functions.h"

HEADER* headOfHeap = NULL;

/// @brief New malloc function. Allocate SIZE bytes of memory.
/// @param size Size to allocate.
/// @return Void pointer to the allocated space, or NULL if there is insufficient memory available.
void *malloc_3is(size_t size)
{
    HEADER* returnValue = NULL;
    
    if (0 == size)
    {
        return returnValue;
    }

    HEADER* currentElement = headOfHeap;
    HEADER* previousElement = NULL;

    while(NULL != currentElement)
    {
        // If the size is big enough, use the given block.
        if (currentElement->bloc_size == size)
        {
            if (headOfHeap == currentElement)
            {
                headOfHeap = headOfHeap->ptr_next;
            }
            else
            {
                previousElement->ptr_next = currentElement->ptr_next;
            }
            currentElement->ptr_next = NULL;
            returnValue = currentElement;
            
            break;
        }
        previousElement = currentElement;
        currentElement = currentElement->ptr_next;
    }

    if (NULL == currentElement)
    {
        HEADER* currentStateOfHeap = sbrk(sizeof(HEADER) + size + sizeof(long));
        currentStateOfHeap->ptr_next = NULL;
        currentStateOfHeap->bloc_size = size;
        currentStateOfHeap->magic_number = MAGIC_NUMBER;

        long* adressOfTail = (void*) (currentStateOfHeap) + size + sizeof(HEADER);
        *adressOfTail = MAGIC_NUMBER;

        returnValue = currentStateOfHeap;
    }
    
    return returnValue + 1;
}

/// @brief New free function. Free a block allocated by 'malloc'.
/// @param ptr Pointer to de-allocate.
void free_3is(void *ptr)
{
    // Add the new free block at head of the heap.
    HEADER* nodeToFree = ((HEADER*)ptr) - 1;
    nodeToFree->ptr_next = headOfHeap;
    headOfHeap = nodeToFree;
}

/// @brief Check if an adress as not been corrupted.
/// @param ptr Pointer to the element to check.
/// @return True if the adress was corrupted, false either.
bool checkIfAdressCorrect(void* ptr)
{
    HEADER* nodeToCheck = (HEADER*) (ptr) - 1;
    
    // Check the magic number in the header
    bool firstCheck = (MAGIC_NUMBER == nodeToCheck->magic_number);
    
    // Check the magic number at the tail of the structure.
    long* adressOfTail = (long*) (ptr + nodeToCheck->bloc_size);
    bool secondCheck = (MAGIC_NUMBER == *adressOfTail);

    return firstCheck && secondCheck;
}
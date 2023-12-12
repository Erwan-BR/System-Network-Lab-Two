#include "./functions.h"

HEADER* headOfHeap = NULL;

/// @brief New malloc function. Allocate SIZE bytes of memory.
/// @param size Size to allocate.
/// @return Void pointer to the allocated space, or NULL if there is insufficient memory available.
void *malloc_3is(size_t size)
{
    void* returnValue = NULL;
    
    if (0 == size)
    {
        return returnValue;
    }

    //HEADER* currentElement = headOfHeap;
    //HEADER* previousElement = NULL;

    HEADER* currentStateOfHeap = sbrk(sizeof(HEADER) + size + sizeof(long));
    currentStateOfHeap->ptr_next = NULL;
    currentStateOfHeap->bloc_size = size;
    currentStateOfHeap->magic_number = MAGIC_NUMBER;

    returnValue = currentStateOfHeap + 1;
    return returnValue;

    /*while(NULL != currentElement)
    {
        if (size == currentElement->bloc_size)
        {
            previousElement->ptr_next = currentElement->ptr_next;
            currentElement = newElementOfHeap;
            break;
        }
        else if (size > currentElement->bloc_size)
        {
            // If the size allows it, split it into two blocks.
            if (size >= (sizeof(HEADER) + sizeof(long) + 1) + sizeof(newElementOfHeap))
            {
                HEADER* newElementForFilling ;
                newElementForFilling->ptr_next = currentElement->ptr_next;
                newElementForFilling->bloc_size = currentElement->bloc_size - sizeof(newElementOfHeap);
                newElementForFilling->magic_number = MAGIC_NUMBER;

                previousElement->ptr_next = newElementForFilling;
                currentElement = newElementOfHeap;
            }
            // Else, juste create the bloc
            else
            {
                previousElement->ptr_next = currentElement->ptr_next;
                currentElement = newElementOfHeap;
            }
            break;
        }
        previousElement = currentElement;
        currentElement = currentElement->ptr_next;
    }*/
    // Check if the value has been placed nowhere in the linked list.
    // It would mean that we reached the end of the linked list.
    /*if (currentElement != NULL)
    {
        returnValue = previousElement + sizeof(previousElement) + sizeof(struct HEADER_TAG *) + sizeof(size) + sizeof(MAGIC_NUMBER);
        return returnValue;
    }*/
    // If this line is reached, it means that an element has been found of the size desired (at least)
    // Deleting the element from the linked list.
    //return returnValue;
}

/// @brief New free function. Free a block allocated by 'malloc'.
/// @param ptr Pointer to de-allocate.
void free_3is(void *ptr)
{
    /*HEADER* currentElement = headOfHeap;
    HEADER* previousElement = NULL;

    while (ptr != currentElement)
    {
        previousElement = currentElement;
        currentElement = currentElement->ptr_next;
    }

    previousElement->ptr_next = currentElement->ptr_next;*/

    // Check if the Magic number has been modified.

    // 

    HEADER* nodeToFree = ptr - sizeof(HEADER);
    nodeToFree->ptr_next = NULL;
    /*nodeToFree->bloc_size = ptr - sizeof(MAGIC_NUMBER);
    nodeToFree->magic_number = MAGIC_NUMBER;*/
    /*HEADER* currentElement = headOfHeap;
    HEADER* previousElement = NULL;

    while (NULL != currentElement)
    {
        previousElement = currentElement;
        currentElement = currentElement->ptr_next;
    }

    previousElement->ptr_next = nodeToFree;*/

    nodeToFree->ptr_next = headOfHeap;
    headOfHeap = nodeToFree;
}
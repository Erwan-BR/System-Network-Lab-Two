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
        // If the size is the same size as a element that has been free, use the given block.
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
        // If the bloc can be split in two for this one and another one for the futur, do it
        if (currentElement->bloc_size > (size + sizeof(HEADER) + 1 + sizeof(MAGIC_NUMBER)))
        {
            // Create a new block for the remaining free space
            HEADER *newBlock = (HEADER*)((void*)currentElement + size + sizeof(HEADER) + sizeof(MAGIC_NUMBER));
            newBlock->bloc_size = currentElement->bloc_size - (size + sizeof(HEADER) + sizeof(MAGIC_NUMBER));
            newBlock->magic_number = MAGIC_NUMBER;

            //Write a new magic number to end the turned block early
            //The new block will keep the previous magic number
            long* adressOfMagicNumber = (void*) (currentElement) + size + sizeof(HEADER);
            *adressOfMagicNumber = MAGIC_NUMBER;

            //Put the new bloc in the Linked List and remove the returned one
            if (headOfHeap == currentElement)
            {
                newBlock->ptr_next = headOfHeap->ptr_next;
                headOfHeap = newBlock;
            }
            else
            {
                newBlock->ptr_next = currentElement->ptr_next;
                previousElement->ptr_next = newBlock;
            }
            
            //Update Returned block header
            currentElement->bloc_size = size;
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
    HEADER* blockToFree = ((HEADER*)ptr) - 1;

    // If the list is empty or the block to free should be inserted at the beginning
    if (headOfHeap == NULL || blockToFree < headOfHeap)
    {
        blockToFree->ptr_next = headOfHeap;
        headOfHeap = blockToFree;
    }
    else
    {
        HEADER* current = headOfHeap;
        HEADER* previous = NULL;

        // Traverse the list to find the correct position to insert the block
        while (current != NULL && current < blockToFree)
        {
            previous = current;
            current = current->ptr_next;
        }

        //Check if the previous block is adjacent to the freed one to fuse them
        linkBlocks(blockToFree,current);
        linkBlocks(previous,blockToFree);
    }
}

/// @brief Try to fuse the two block, else link them in the linked list
/// @param ptr1 First Block ie (ptr1 < ptr2)
/// @param ptr2 Second Block
void linkBlocks(HEADER* ptr1, HEADER* ptr2){
    //Check if the blocks are adjacents to fuse them
    if((void*) ptr1+ptr1->bloc_size+sizeof(HEADER)+sizeof(MAGIC_NUMBER) == ptr2){
        ptr1->bloc_size = ptr1->bloc_size + +sizeof(HEADER)+sizeof(MAGIC_NUMBER) +ptr2->bloc_size;
        ptr1->ptr_next = ptr2->ptr_next;
    }
    //Else, just link them in the List
    else{
        ptr1->ptr_next = ptr2;
    }
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
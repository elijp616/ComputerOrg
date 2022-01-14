/*
 * CS 2110 Homework 10 Spring 2021
 * Author:
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"

/* Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */

/* Our freelist structure - our freelist is represented as a singly linked list
 * the freelist is sorted by address;
 */
metadata_t *address_list;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

static void remove_list(metadata_t* block) {
    metadata_t* curr = address_list;
    metadata_t* prev = NULL;
    while (curr != NULL && block != curr) {
        prev = curr;
        curr = curr->next;
    }
    if (prev != NULL) {
        if (curr != NULL){
            prev->next = curr->next;
        }
    } else {
        address_list = curr->next;
    }
}
static void addToList(metadata_t* memory) {
    if (address_list == NULL) {
        address_list = memory;
        return;
    }
    metadata_t* curr = address_list;
    metadata_t* prev = NULL;
    while (curr != NULL && (memory->size > curr->size)) {
        prev = curr;
        curr = curr->next;
    }
    memory->next = curr;
    if (prev == NULL) {
        address_list = memory;
    } else {
        prev->next = memory;
    }
}


static void mymerge(metadata_t* memory) {
    //printStuff();
    metadata_t* node1 = address_list;
    while (node1 != NULL) {
        if ((uint8_t*)node1 + node1->size == (uint8_t*)memory) {
            //left
            node1->size += memory->size;
            remove_list(memory);
            remove_list(node1);
            addToList(node1);
            memory = node1;
            node1 = address_list;
        } else if ((uint8_t*)memory + memory->size == (uint8_t*)node1) {
            //right
            memory->size += node1->size;
            remove_list(node1);
            remove_list(memory);
            addToList(memory);
            node1 = address_list;
        } else {
            //neither
            node1 = node1->next;
        }
    }
}





// -------------------- PART 1: Helper functions --------------------

/* The following prototypes represent useful helper functions that you may want
 * to use when writing your malloc functions. You do not have to implement them
 * first, but we recommend reading over their documentation and prototypes;
 * having a good idea of the kinds of helpers you can use will make it easier to
 * plan your code.
 *
 * None of these functions will be graded individually. However, implementing
 * and using these will make programming easier. We may provide ungraded test
 * cases for some of these functions after the assignment is released.
 */


/* OPTIONAL HELPER FUNCTION: find_right
 * Given a pointer to a free block, this function searches the freelist for another block to the right of the provided block.
 * If there is a free block that is directly next to the provided block on its right side,
 * then return a pointer to the start of the right-side block.
 * Otherwise, return null.
 * This function may be useful when implementing my_free().

 */

static void merge(metadata_t *left, metadata_t *right)
{
    left->size += right->size;
    left->next = right->next;
}



/* OPTIONAL HELPER FUNCTION: merge
 * This function should take two pointers to blocks and merge them together.
 * The most important step is to increase the total size of the left block to include the size of the right block.
 * You should also copy the right block's next pointer to the left block's next pointer. If both blocks are initially in the address_list, this will remove the right block from the list.
 * This function will be useful for both my_malloc() (when you have to merge sbrk'd blocks) and my_free().
 */

/* OPTIONAL HELPER FUNCTION: split_block
 * This function should take a pointer to a large block and a requested size, split the block in two, and return a pointer to the new block (the right part of the split).
 * Remember that you must make the right side have the user-requested size when splitting. The left side of the split should have the remaining data.
 * We recommend doing the following steps:
 * 1. Compute the total amount of memory that the new block will take up (both metadata and user data).
 * 2. Using the new block's total size with the address and size of the old block, compute the address of the start of the new block.
 * 3. Shrink the size of the old/left block to account for the lost size. This block should stay in the address_list.
 * 4. Set the size of the new/right block and return it. This block should not go in the address_list.
 * This function will be useful for my_malloc(), particularly when the best-fit block is big enough to be split.
 */
static metadata_t *split_block(metadata_t *block, size_t size)
{
    // 1. Compute the total amount of memory that the new block will take up (both metadata and user data).
    // 2. Using the new block's total size with the address and size of the old block, compute the address of the start of the new block.
    //* 3. Shrink the size of the old/left block to account for the lost size. This block should stay in the address_list.
    //* 4. Set the size of the new/right block and return it. This block should not go in the address_list.
    uintptr_t sizeOfLeft = 0;
    sizeOfLeft=size+TOTAL_METADATA_SIZE;
    metadata_t *i=(metadata_t*)((uintptr_t)(block)+block->size+TOTAL_METADATA_SIZE-(uintptr_t)sizeOfLeft);
    block->size=block->size-sizeOfLeft;
    if (i != NULL)
    {
        i->size = size;
        i->next = NULL;
    }
    return i;
}


/* OPTIONAL HELPER FUNCTION: add_to_addr_list
 * This function should add a block to address_list.
 * Remember that the address_list must be sorted by address. You can compare the addresses of blocks by comparing the metadata_t pointers like numbers (do not dereference them).
 * Don't forget about the case where the address_list is empty. Remember what you learned from Homework 9.
 * This function will be useful for my_malloc() (mainly for adding in sbrk blocks) and my_free().
 */
static void add_to_addr_list(metadata_t *block)
{
    if (address_list == NULL)
    {
    address_list = block;
    }
    else
    {
        metadata_t* currentNode = address_list;
        metadata_t* previousNode = NULL;
        //Now, iterate using currentNoderent and previousNodeious nodes
        while (currentNode!=NULL && ((uintptr_t)block>(uintptr_t)currentNode))
         {
                previousNode = currentNode;
                currentNode = currentNode->next;
        }
        block->next = currentNode;
        if ((metadata_t*)((char*)block+block->size)==currentNode)
        {
            merge(block,block->next);
        }
        if (previousNode == NULL)
        {
            address_list = block;
        }
        else
        {
            previousNode->next = block;
            if ((metadata_t*)((char*)previousNode+previousNode->size)==block)
            {
                merge(previousNode,currentNode);
            }
        }
    }
}


/* OPTIONAL HELPER FUNCTION: remove_from_addr_list
 * This function should remove a block from the address_list.
 * Simply search through the address_list, looking for a node whose address matches the provided block's address.
 * This function will be useful for my_malloc(), particularly when the best-fit block is not big enough to be split.
 */
static void remove_from_addr_list(metadata_t *block)
{
    metadata_t *i;
    for (i=address_list;!(i<block && block<i->next);i=i->next)
    {
        if ((i>=i->next) && (block>i || block<i->next))
        {
            break;
        }
    }
    i->next=block->next;
}

/* OPTIONAL HELPER FUNCTION: find_best_fit
 * This function should find and return a pointer to the best-fit block. See the PDF for the best-fit criteria.
 * Remember that if you find the perfectly sized block, you should return it immediately.
 * You should not return an imperfectly sized block until you have searched the entire list for a potential perfect block.
 */
static metadata_t *find_best_fit(size_t size)
{
    metadata_t *i;
    if (address_list == NULL)
    {
        return NULL;
    }
    for (i=address_list;((i->next) && (i->size<size));i=i->next)
    {
        //idk
    }
    if (i != NULL)
    {
        if (i->size>size+MIN_BLOCK_SIZE)
        {
            i=split_block(i, size);
            return i;
        }
        else
        {
            i->next=NULL;
            return i;
        }
    }
    return NULL;
}





// ------------------------- PART 2: Malloc functions -------------------------

/* Before starting each of these functions, you should:
 * 1. Understand what the function should do, what it should return, and what the address_list should look like after it finishes
 * 2. Develop a high-level plan for how to implement it; maybe sketch out pseudocode
 * 3. Check if the parameters have any special cases that need to be handled (when they're NULL, 0, etc.)
 * 4. Consider what edge cases the implementation needs to handle
 * 5. Think about any helper functions above that might be useful, and implement them if you haven't already
 */


/* MALLOC
 * See PDF for documentation
 */
void *my_malloc(size_t size)
{
    // Reminder of how to do malloc:
    // 1. Make sure the size is not too small or too big.
    // 2. Search for a best-fit block. See the PDF for information about what to check.
    // 3. If a block was not found:
    // 3.a. Call sbrk to get a new block.
    // 3.b. If sbrk fails (which means it returns -1), return NULL.
    // 3.c. If sbrk succeeds, add the new block to the address_list. If the new block is next to another block in the address_list, merge them.
    // 3.d. Go to step 2.
    // 4. If the block is too small to be split (see PDF for info regarding this), then remove the block from the address_list and return a pointer to the block's user section.
    // 5. If the block is big enough to split:
    // 5.a. Split the block into a left side and a right side. The right side should be the perfect size for the user's requested data.
    // 5.b. Keep the left side in the address_list.
    // 5.c. Return a pointer to the user section of the right side block.
    // A lot of these steps can be simplified by implementing helper functions. We highly recommend doing this!

    my_malloc_errno = NO_ERROR;
    if (size==0)
    {
        my_malloc_errno=NO_ERROR;
        return NULL;
    }
    if(size>SBRK_SIZE-TOTAL_METADATA_SIZE)
    {
        my_malloc_errno=SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }
   
    metadata_t *point;
    long unsigned int hold = -1;
    if(!address_list)
    {
        point=(metadata_t *)my_sbrk(SBRK_SIZE);
        if((uintptr_t)point == hold || !point)
        {
            my_malloc_errno=OUT_OF_MEMORY;
            return NULL;
        }
        address_list = point;
        address_list->size = size;
        address_list->next = NULL;
       
    }
    point = find_best_fit(size);
    return (void*)((uintptr_t)point+TOTAL_METADATA_SIZE);
}


/* REALLOC
 * See PDF for documentation
 */
void *my_realloc(void *ptr, size_t size) {
        if (ptr == NULL) {
        my_malloc_errno = NO_ERROR;
        return my_malloc(size);
    }
    if (size == 0) {
        my_free(ptr);
        return NULL;
    }
    char* newPtr = my_malloc(size);
    memcpy(newPtr, ptr, size);
    my_free(ptr);
    return newPtr;

    // Reminder of how to do realloc:
    // 1. If ptr is NULL, then only call my_malloc(size). If the size is 0, then only call my_free(ptr).
    // 2. Call my_malloc to allocate the requested number of bytes. If this fails, immediately return NULL and do not free the old allocation.
    // 3. Copy the data from the old allocation to the new allocation. We recommend using memcpy to do this. Be careful not to read or write out-of-bounds!
    // 4. Free the old allocation and return the new allocation.

}

/* CALLOC
 * See PDF for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
    if (!nmemb && !size && (int) size <= 0) {
        return NULL;
    }
    size_t sz = nmemb * size;
    void* pointer = my_malloc(sz);
    if (pointer == NULL) {
        return NULL;
    }
    char* temp = pointer;
    while (sz) {
        *temp = 0;
        temp++;
        sz--;
    }
    return pointer;

    // Reminder for how to do calloc:
    // 1. Use my_malloc to allocate the appropriate amount of size.
    // 2. Clear all of the bytes that were allocated. We recommend using memset to do this.

}

/* FREE
 * See PDF for documentation
 */
void my_free(void *ptr) {
    my_malloc_errno = NO_ERROR;
    if (ptr == NULL) {
        return;
    }
    metadata_t* block = (metadata_t*) ((char*) ptr - sizeof(metadata_t));

    //if canaries aren't corrupted, add the block back to the freelist and you're good
    add_to_addr_list(block);
    //set error accordingly
    my_malloc_errno = NO_ERROR;
}

    // Reminder for how to do free:
    // 1. Since ptr points to the start of the user block, obtain a pointer to the metadata for the freed block.
    // 2. Look for blocks in the freelist that are positioned immediately before or after the freed block.
    // 2.a. If a block is found before or after the freed block, then merge the blocks.
    // 3. Once the freed block has been merged (if needed), add the freed block back to the freelist.
    // 4. Alternatively, you can do step 3 before step 2. Add the freed block back to the freelist,
    // then search through the freelist for consecutive blocks that need to be merged.

    // A lot of these steps can be simplified by implementing helper functions. We highly recommend doing this!



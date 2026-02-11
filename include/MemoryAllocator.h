#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include "BlockHeader.h"
#include <cstddef>

/*
    MemoryAllocator

    A custom heap manager that mimics the behavior of malloc/free.

    Features:
    - Private 1 MB heap
    - Block splitting and coalescing
    - Separate free list for faster allocation
    - Support for First Fit and Best Fit strategies
    - Heap visualization and statistics
    - Safety checks (double free, invalid free)

    The allocator manages memory using BlockHeader metadata placed
    before every payload region inside the heap.
*/

class MemoryAllocator {
public:
    // -------- Allocation Strategy --------
    enum FitStrategy { FIRST_FIT, BEST_FIT };

    // Constructor allows selecting allocation strategy
    MemoryAllocator(FitStrategy strat = FIRST_FIT);

    // Allocates memory of requested size from custom heap
    void* myMalloc(size_t size);

    // Frees previously allocated memory
    void myFree(void* ptr);

    // Debugging utilities
    void printHeapLayout();   // Shows blocks in heap order
    void printStats();        // Shows used/free memory statistics
    void printMemoryMap();    // Visual memory map representation

private:
    // Total heap size managed by this allocator (1 MB)
    static const size_t HEAP_SIZE = 1024 * 1024;

    // Raw memory buffer representing the custom heap
    static char heap[HEAP_SIZE];   

    // Pointer to the first block in heap order
    BlockHeader* heapStart;

    // Head of the free list (contains only free blocks)
    BlockHeader* freeListHead;

    // Current strategy being used
    FitStrategy strategy;

    // -------- Internal Helper Functions --------

    // Finds a suitable free block based on the selected strategy
    BlockHeader* findFreeBlock(size_t size);

    // Splits a large block into allocated part and remaining free part
    void splitBlock(BlockHeader* block, size_t size);

    // Merges adjacent free blocks to reduce fragmentation
    void coalesce(BlockHeader* block);
};

#endif
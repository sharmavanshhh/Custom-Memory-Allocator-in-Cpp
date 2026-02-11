#include "MemoryAllocator.h"
#include <iostream>

// Definition of static heap storage
alignas(BlockHeader) char MemoryAllocator::heap[MemoryAllocator::HEAP_SIZE];

/*
    Constructor
    Initializes the entire heap as a single large free block.
*/
MemoryAllocator::MemoryAllocator(FitStrategy strat) : strategy(strat) {
    void* start = static_cast<void*>(heap);

    // Properly construct BlockHeader in raw heap memory
    heapStart = new (start) BlockHeader();

    heapStart->size = HEAP_SIZE - sizeof(BlockHeader);
    heapStart->isFree = true;

    heapStart->prev = nullptr;
    heapStart->next = nullptr;

    heapStart->prevFree = nullptr;
    heapStart->nextFree = nullptr;

    freeListHead = heapStart;
}

/*
    Utility: Prints all blocks in heap order.
*/
void MemoryAllocator::printHeapLayout() {
    BlockHeader* current = heapStart;

    std::cout << "\nHeap Layout:\n";
    while (current) {
        std::cout << "[ "
                  << (current->isFree ? "Free" : "Used")
                  << " | Size: " << current->size
                  << " ] -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}

/*
    Finds a suitable free block using selected strategy.
*/
BlockHeader* MemoryAllocator::findFreeBlock(size_t size) {
    BlockHeader* current = freeListHead;
    BlockHeader* bestBlock = nullptr;

    while (current) {
        if (current->isFree && current->size >= size) {
            if (strategy == FIRST_FIT) {
                return current;
            }

            if (strategy == BEST_FIT) {
                if (!bestBlock || current->size < bestBlock->size) {
                    bestBlock = current;
                }
            }
        }
        current = current->nextFree;
    }

    return bestBlock;
}

/*
    Align requested size to 8-byte boundary.
*/
static size_t alignSize(size_t size) {
    const size_t ALIGNMENT = 8;
    return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

/*
    Splits a block into:
    [Allocated block] + [Remaining free block]
    Only modifies heap structure, NOT free list.
*/
void MemoryAllocator::splitBlock(BlockHeader* block, size_t size) {
    if (block->size < size + sizeof(BlockHeader) + 8) {
        return;  // Not enough space to split
    }

    char* newBlockAddress =
        reinterpret_cast<char*>(block) + sizeof(BlockHeader) + size;

    BlockHeader* newBlock =
        new (newBlockAddress) BlockHeader();

    newBlock->size = block->size - size - sizeof(BlockHeader);
    newBlock->isFree = true;

    // Heap linking
    newBlock->next = block->next;
    newBlock->prev = block;

    if (block->next) {
        block->next->prev = newBlock;
    }

    block->next = newBlock;
    block->size = size;
}

/*
    Allocates memory from the custom heap.
*/
void* MemoryAllocator::myMalloc(size_t size) {
    if (size == 0) return nullptr;

    size = alignSize(size);

    BlockHeader* block = findFreeBlock(size);
    if (!block) return nullptr;

    // Remove chosen block from free list
    if (block->prevFree) {
        block->prevFree->nextFree = block->nextFree;
    } else {
        freeListHead = block->nextFree;
    }

    if (block->nextFree) {
        block->nextFree->prevFree = block->prevFree;
    }

    block->nextFree = nullptr;
    block->prevFree = nullptr;

    // Split if large enough
    splitBlock(block, size);

    // If split created a new free block, add it to free list
    BlockHeader* newBlock = block->next;
    if (newBlock && newBlock->isFree) {
        newBlock->nextFree = freeListHead;
        newBlock->prevFree = nullptr;

        if (freeListHead) {
            freeListHead->prevFree = newBlock;
        }

        freeListHead = newBlock;
    }

    block->isFree = false;

    return reinterpret_cast<char*>(block) + sizeof(BlockHeader);
}

/*
    Coalesces adjacent free blocks to reduce fragmentation.
*/
void MemoryAllocator::coalesce(BlockHeader* block) {
    // Merge with next
    if (block->next && block->next->isFree) {
        BlockHeader* nextBlock = block->next;

        // Remove nextBlock from free list
        if (nextBlock->prevFree) {
            nextBlock->prevFree->nextFree = nextBlock->nextFree;
        } else {
            freeListHead = nextBlock->nextFree;
        }

        if (nextBlock->nextFree) {
            nextBlock->nextFree->prevFree = nextBlock->prevFree;
        }

        block->size += sizeof(BlockHeader) + nextBlock->size;
        block->next = nextBlock->next;

        if (nextBlock->next) {
            nextBlock->next->prev = block;
        }
    }

    // Merge with previous
    if (block->prev && block->prev->isFree) {
        BlockHeader* prevBlock = block->prev;

        prevBlock->size += sizeof(BlockHeader) + block->size;
        prevBlock->next = block->next;

        if (block->next) {
            block->next->prev = prevBlock;
        }
    }
}

/*
    Frees previously allocated memory.
    Includes safety checks for invalid and double free.
*/
void MemoryAllocator::myFree(void* ptr) {
    if (!ptr) return;

    if (ptr < (void*)heap || ptr >= (void*)(heap + HEAP_SIZE)) {
        std::cout << "Error: Invalid pointer! Not from allocator heap.\n";
        return;
    }

    BlockHeader* block = reinterpret_cast<BlockHeader*>(
        reinterpret_cast<char*>(ptr) - sizeof(BlockHeader)
    );

    if (block->isFree) {
        std::cout << "Error: Double free detected!\n";
        return;
    }

    block->isFree = true;

    // Add block to free list
    block->nextFree = freeListHead;
    block->prevFree = nullptr;

    if (freeListHead) {
        freeListHead->prevFree = block;
    }

    freeListHead = block;

    coalesce(block);
}

/*
    Prints memory usage statistics.
*/
void MemoryAllocator::printStats() {
    BlockHeader* current = heapStart;

    size_t totalUsed = 0;
    size_t totalFree = 0;
    int freeBlocks = 0;

    while (current) {
        if (current->isFree) {
            totalFree += current->size;
            freeBlocks++;
        } else {
            totalUsed += current->size;
        }
        current = current->next;
    }

    std::cout << "\nHeap Statistics:\n";
    std::cout << "Total Used Memory: " << totalUsed << " bytes\n";
    std::cout << "Total Free Memory: " << totalFree << " bytes\n";
    std::cout << "Number of Free Blocks (Fragmentation): " << freeBlocks << "\n";
}

/*
    Visual representation of memory blocks.
*/
void MemoryAllocator::printMemoryMap() {
    BlockHeader* current = heapStart;

    std::cout << "\nMemory Map:\n|";
    while (current) {
        std::cout << (current->isFree ? "F" : "U")
                  << current->size << "|";
        current = current->next;
    }
    std::cout << "\n";
}

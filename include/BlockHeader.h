#ifndef BLOCK_HEADER_H
#define BLOCK_HEADER_H

#include <cstddef>

/*
    BlockHeader represents the metadata stored before every memory block
    inside our custom heap.

    Layout in memory:

    | BlockHeader | ----------- Payload (user memory) ----------- |

    The user never sees this header. It is used internally by the allocator
    to manage memory blocks, perform splitting, coalescing, and maintain
    free/used lists.
*/

struct BlockHeader {
    // Size of the usable memory (payload) in this block
    size_t size;

    // Indicates whether this block is currently free or allocated
    bool isFree;

    // ---------------- Heap Order Links ----------------
    // These pointers link ALL blocks in the heap in physical order.
    // Used for traversal and coalescing adjacent blocks.
    BlockHeader* prev;
    BlockHeader* next;

    // ---------------- Free List Links ----------------
    // These pointers link ONLY free blocks for faster allocation search.
    BlockHeader* prevFree;
    BlockHeader* nextFree;
};

#endif

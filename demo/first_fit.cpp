#include <iostream>
#include "MemoryAllocator.h"

int main() {
    std::cout << "\n================ FIRST FIT DEMO ================\n";

    MemoryAllocator allocator(MemoryAllocator::FIRST_FIT);

    std::cout << "\n[STEP 1] Initial Heap\n";
    allocator.printHeapLayout();
    allocator.printStats();

    std::cout << "\n[STEP 2] Allocate A(40), B(80), C(24)\n";
    void* A = allocator.myMalloc(40);
    void* B = allocator.myMalloc(80);
    void* C = allocator.myMalloc(24);
    allocator.printMemoryMap();
    allocator.printStats();

    std::cout << "\n[STEP 3] Free B to create fragmentation\n";
    allocator.myFree(B);
    allocator.printMemoryMap();
    allocator.printStats();

    std::cout << "\n[STEP 4] Allocate D(32) - FIRST FIT picks first hole\n";
    void* D = allocator.myMalloc(32);
    allocator.printMemoryMap();
    allocator.printStats();

    std::cout << "\n[STEP 5] Double Free Test on D\n";
    allocator.myFree(D);
    allocator.myFree(D);   // error

    std::cout << "\n[STEP 6] Invalid Free Test\n";
    int x;
    allocator.myFree(&x);  // error

    std::cout << "\n[STEP 7] Free remaining blocks to test Coalescing\n";
    allocator.myFree(A);
    allocator.myFree(C);

    allocator.printHeapLayout();
    allocator.printStats();

    std::cout << "\n================ END FIRST FIT DEMO ================\n";
    return 0;
}

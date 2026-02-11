#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    char* a = (char*)malloc(24);
    char* b = (char*)malloc(24);
    char* c = (char*)malloc(24);

    cout << "A: " << (void*)a << "\n";
    cout << "B: " << (void*)b << "\n";
    cout << "C: " << (void*)c << "\n\n";

    free(a);
    free(c);

    // abhi fragmentation state
    char* fail = (char*)malloc(40);
    cout << "Try 40 before freeing B: " << (void*)fail << "\n";

    free(b); // ab teenon free, coalescing possible

    char* big = (char*)malloc(40);
    cout << "40 after freeing B (coalesced): " << (void*)big << "\n";

    free(fail);
    free(big);
}

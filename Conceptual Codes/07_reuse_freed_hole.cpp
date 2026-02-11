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

    free(b);  // middle hole

    char* d = (char*)malloc(20); // slightly smaller than 24
    cout << "D (should reuse B): " << (void*)d << "\n";

    free(a); free(c); free(d);
}

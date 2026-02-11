#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    char* a = (char*)malloc(20);
    char* b = (char*)malloc(20);
    char* c = (char*)malloc(20);

    cout << "A: " << (void*)a << "\n";
    cout << "B: " << (void*)b << "\n";
    cout << "C: " << (void*)c << "\n\n";

    free(a);
    free(c);

    cout << "Freed A and C\n\n";

    char* big = (char*)malloc(35);

    cout << "Big: " << (void*)big << "\n";

    free(b);
    free(big);
}

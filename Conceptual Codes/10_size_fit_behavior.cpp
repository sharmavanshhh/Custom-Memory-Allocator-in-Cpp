#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    char* a = (char*)malloc(32);
    char* b = (char*)malloc(32);

    cout << "A: " << (void*)a << "\n";
    cout << "B: " << (void*)b << "\n\n";

    free(a);

    char* small = (char*)malloc(16);
    cout << "Small (fits in A): " << (void*)small << "\n";

    char* large = (char*)malloc(40);
    cout << "Large (won't fit in A): " << (void*)large << "\n";

    free(b);
    free(small);
    free(large);
}

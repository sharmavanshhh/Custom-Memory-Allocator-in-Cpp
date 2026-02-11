#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    char* a = (char*)malloc(20);
    char* b = (char*)malloc(20);
    char* c = (char*)malloc(20);

    cout << "Before free, b at: " << (void*)b << "\n";

    free(b);

    char* d = (char*)malloc(18);

    cout << "After reuse, d at: " << (void*)d << "\n";

    free(a);
    free(c);
    free(d);
}

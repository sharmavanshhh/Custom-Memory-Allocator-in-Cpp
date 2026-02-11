#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    char* a = (char*)malloc(20);
    char* b = (char*)malloc(20);

    cout << "A: " << (void*)a << "\n";
    cout << "B: " << (void*)b << "\n";

    free(a);
    free(b);
}

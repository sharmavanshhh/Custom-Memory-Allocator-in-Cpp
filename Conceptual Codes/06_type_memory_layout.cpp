#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // 40 bytes allocate
    char* p = (char*)malloc(40);

    cout << "Base address p: " << (void*)p << "\n\n";

    // Treat same memory as char array
    cout << "CHAR view (1 byte each):\n";
    for (int i = 0; i < 5; i++) {
        cout << "p + " << i << " : " << (void*)(p + i) << "\n";
    }

    cout << "\nINT view (4 bytes each):\n";

    // Treat same memory as int array
    int* q = (int*)p;

    for (int i = 0; i < 3; i++) {
        cout << "q + " << i 
             << " : " << (void*)(q + i) 
             << "  (difference from p: "
             << ((char*)(q + i) - p) << " bytes)\n";
    }

    free(p);
}

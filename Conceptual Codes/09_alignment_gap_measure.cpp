#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    char* p1 = (char*)malloc(13);
    char* p2 = (char*)malloc(13);

    cout << "P1: " << (void*)p1 << "\n";
    cout << "P2: " << (void*)p2 << "\n";

    cout << "Gap (bytes): " << (char*)p2 - (char*)p1 << "\n";

    free(p1);
    free(p2);
}

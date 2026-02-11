#include<iostream>
#include<cstdlib>

using namespace std;

int main(){
    char* p = (char*)malloc(40);

    cout << "Contgous Addresses: " << endl;

    for(int i = 0; i < 40; i++){
        cout << (void*)(p + i) << endl;
    }

    free(p);
}
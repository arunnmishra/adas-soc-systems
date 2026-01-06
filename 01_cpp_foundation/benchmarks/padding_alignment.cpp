#include<iostream>
#include<vector>

using namespace std;

#pragma pack(push, 1)
struct A {
    char c; //1 byte
    int  i; //4 bytes -> 8 bytes with padding
    char d; //1 byte  -> 12 bytes
};
#pragma pack(pop)
//Packed version saves memory but risks misaligned access and performance loss
//Packed structs are for talking to the outside world, not for doing work inside our system.

struct B {
    int  i; //4 bytes
    char c; //1 byte
    char d; //1 byte -> 8 bytes with padding
};

int main(void) {
    cout << "Size of struct A: " << sizeof(A) << " bytes" << endl;
    cout << "Size of struct B: " << sizeof(B) << " bytes" << endl;

    return 0;
}
#include<iostream>
#include<vector>

using namespace std;

struct MyStruct {
    char a;        // 1 byte
    // 3 bytes padding here for alignment
    int b;        // 4 bytes
    double c;     // 8 bytes
};


void main(void) {
    cout << "Size of MyStruct: " << sizeof(MyStruct) << " bytes" << endl;

    // Stack allocation
    MyStruct stackObj;
    cout << "Address of stackObj: " << &stackObj << endl;

    // Heap allocation
    MyStruct* heapObj = new MyStruct();
    cout << "Address of heapObj: " << heapObj << endl;

    // Object contiguity in a vector
    vector<MyStruct> vec(3);
    cout << "Addresses of vector elements:" << endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << "Element " << i << ": " << &vec[i] << endl;
    }

    delete heapObj;
}
#include<iostream>
#include<vector>

using namespace std;

//typical word size is 4 or 8 bytes depending on architecture
class ClassWithPadding1 {
    char a;       // 1 byte  
    int b;        // 4 bytes
    // 3 bytes padding here for alignment considering typical 8-byte alignment
    double c;     // 8 bytes
};

class ClassWithPadding2 {    
public:  
    // 3 bytes padding here for alignment considering typical 8-byte alignment
    int b;        // 4 bytes
    double c;     // 8 bytes
    char a;       // 1 byte   
    
}obj1;

int main(void) {
    cout << "Size of ClassWithPadding1: " << sizeof(ClassWithPadding1) << " bytes" << endl;
    cout << "Size of ClassWithPadding2: " << sizeof(ClassWithPadding2) << " bytes" << endl;
    cout << "Address of b: " << (void *)&(obj1.b) << endl;
    cout << "Address of a: " << (void *)&(obj1.c) << endl;
    cout << "Address of c: " << (void *)&(obj1.a) << endl;

    // Stack allocation
    ClassWithPadding2 stackObj;
    cout << "Address of stackObj: " << &stackObj << endl;

    // Heap allocation
    ClassWithPadding1* heapObj = new ClassWithPadding1();
    cout << "Address of heapObj: " << heapObj << endl;

    // Object contiguity in a vector on stack
    vector<ClassWithPadding1> vec1(3);
    // Object contiguity in a vector on heap
    vector<ClassWithPadding1> *vec2 = new vector<ClassWithPadding1>(3); //new returns pointer
    cout << "Addresses of vector elements:" << endl;
    cout <<"Sizeof ClassWithPadding1: " << sizeof(ClassWithPadding1) << " bytes" << endl;
    for (size_t i = 0; i < vec1.size(); ++i) {
        cout << "Element Vec1 " << i << ": " << &vec1[i] << endl;
        cout << "Element Vec2 " << i << ": " << &((*vec2)[i]) << endl;
    }

    delete heapObj;
    delete vec2;

    return 0;
}
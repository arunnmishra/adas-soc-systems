#include <iostream>
#include<string>

using namespace std;

class iHaveConst{
    int a;
    const size_t size;
    mutable int refrences;
public:
    iHaveConst(int a):size(a){
        //const members force explicit construction
        cout<<"iHaveConst Constructed with size: "<<a<<endl;
    }
     size_t get_size(void) const{ 
        refrences++; //only mutable member variable allowed to be altered by const
        return size;
    }
};

int main(void)
{
    const iHaveConst constobj{5};
    cout << constobj.get_size() <<endl; //const object can only access const functions. useful when we pass const object to a function
    //here get_sizesignature is ==> get_size(const iHaveConst *this)

    return 0;
}
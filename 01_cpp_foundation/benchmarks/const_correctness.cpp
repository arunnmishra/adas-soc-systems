#include <iostream>
#include<string>

using namespace std;

class iHaveConst{
    int a;
    const size_t size;
public:
    iHaveConst(int a):size(a){
        cout<<"iHaveConst Constructed with size: "<<a<<endl;
    }
    size_t get_size(void){
        return size;
    }
};

int main(void)
{
    iHaveConst constobj{5};
    cout << constobj.get_size() <<endl; //TODO 

    return 0;
}
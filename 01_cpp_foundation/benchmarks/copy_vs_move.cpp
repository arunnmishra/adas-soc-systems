#include<iostream>
#include<vector>
#include <cstring> 

using namespace std;

//Copy constructor-assignment: understanding the use and the penality

class BigBuffer{
    vector<int> buff;
    string buff_name;
    char *pImpl;            //next make it ==> std::unique_ptr Then re-observe: copy becomes deleted 2- move becomes automatic
public:
    //constructor
    BigBuffer(size_t n=1000000, string s="default buffer"):buff(n), buff_name(s){
        pImpl = new char[sizeof(s) + 1];
        std::strcpy(pImpl,s.c_str());
        cout<<"Constructed."<<endl;
    }
    //copy constructor
    BigBuffer(const BigBuffer &other):buff(other.buff),buff_name(other.buff_name){
        //deep copy, first allocate new memory same as other, then copy 
        pImpl = new char[sizeof(other) + 1];
        std::strcpy(pImpl,other.pImpl);
        cout<<"copy constructed"<<endl;
    }
    //copy assginment 
    BigBuffer &operator=(const BigBuffer & rhs){ // A=B => A.operator=(B) 
        if(&rhs != this){
            buff      = rhs.buff;       //current object already updated.
            buff_name = rhs.buff_name;  //if we forget proper copy for all member it will be ignore 
            delete[] pImpl;
            pImpl = new char[std::strlen(rhs.pImpl) + 1];//deep copy the pImpl
            std::strcpy(pImpl,rhs.pImpl);
        }
        cout<<"copy Assigned"<<endl;
        return *this; //return for efficeicy or chaining 
    }

    //move constructor, to eliminate the copy penality wherever psossible to transfer ownership
    BigBuffer(BigBuffer &&r_value) noexcept :buff(std::move(r_value.buff)),buff_name(std::move(r_value.buff_name)),
                                    pImpl(r_value.pImpl){
        r_value.pImpl = nullptr;
        cout<<"moved constructed."<<endl;
    }

    //move assignment, saves heavylifting by transfering ownership and avoidign copy in case assingment
    BigBuffer & operator=(BigBuffer &&r_value) noexcept{
        if (this != &r_value) {
            buff = std::move(r_value.buff);
            buff_name =std::move(r_value.buff_name);
            pImpl = r_value.pImpl;
            r_value.pImpl = nullptr;
        }
        cout<<"moved assigned."<<endl;
        return *this;
    }

    //destructor 
    ~BigBuffer(){
        delete[] pImpl;
        cout<<this->buff_name<<"Destructed!"<<endl;
    }
};

void func_A(BigBuffer b){
    cout<<"call by value also calls copy=> penality again"<<endl;
}
BigBuffer func_B(){

    cout<<"return by value also calls copy=> penality again"<<endl;
    BigBuffer b(100000);
    return b;
}

int main(void){
    BigBuffer b1(10000000, "buffer#1");       //big b1 buffer. normal constructor shall be called 
    BigBuffer b2{b1};   //copy constructor shall be called
    BigBuffer b3(100);  //new small buffer
    b3 = b2;            //copy assignment shall be called , 
                        //Unintentional copies of large objects are dangerous
                        //out copy constructor shall be efficient or better move to move semantics when ownership transffered 
                        //to avoid this penality
    cout<<"------ while passing  by value ---------"<<endl;
    func_A(b3);         //call by value, again copy, copy constructed
    cout<<"------ while returning by value ---------"<<endl;
    b3 = func_B();      //Again return by value a penality ==> possible copy assignment unless RVO (C++17)
    
    cout<<"------ while adding to container ---------"<<endl;
    vector<BigBuffer> v;
    v.reserve(10);      //this is very important , if we do not resever the size , then every time vector grow that many elecments are recreated
    v.push_back(b3);    //here one more copy constructor

    cout<<"------ move will make life better for ownership transfer ---------"<<endl;
    BigBuffer b4(std::move(b3));  //now it will call move construct 
    b4 = std::move(b2);           //and move assignment, they are by-default unless you implement for pIMPL things 
    cout<<"------ efficient container with move ---------"<<endl;
    v.push_back(std::move(b4)); 
    cout<<"------ efficient container with emplace_back when constructing ---------"<<endl;
    //v.emplace_back(std::move(b4)); //no benifit  
    v.emplace_back(1000,"Emplaced_buff"); //temporary will be avoided , faster than creating a temporary and moving 

    return 0;
}
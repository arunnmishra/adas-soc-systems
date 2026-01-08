#include<iostream>
#include<vector>

using namespace std;
/*
 */

class coordinates{
    int x1,x2,x3;
public:
    int get_sum(void){
        return x1+x2+x3;
    };
    //default constructor 
    coordinates(){
        cout<<"construtor coordinates"<<endl;
    }
    coordinates(int a, int b, int c): x1(a),x2{b}, x3{c}{
        cout<<"3 param construtor coordinates"<<endl;
    }
    coordinates(const coordinates &obj): x1{obj.x1}, x2{obj.x2}, x3{obj.x3} {
        cout<<"copy construtor coordinates"<<endl;
    }
};

class echo_data{
    vector<coordinates> d{10}; //this will call 10x constructor 
    coordinates c{2,4,6}; //this will call a 3 parma constructor 
    char *dp = "data_point1";
public:
    string get_dp_name(){
        return dp;
    };
    //default constructor 
    echo_data(){
        cout<<"construtor echo_data"<<endl;
    }

    //default constructor 
    echo_data(const echo_data & obj): d{obj.d}, c{obj.c}, dp{obj.dp} {
        cout<<"copy construtor echo_data"<<endl;
    }

    //default assignment 
};


int main(void){
    echo_data *data1 = new echo_data();
    echo_data *data2 =data1; //here constructor is not called will see where all copy constructor is called

    echo_data d1;
    cout<<"****************"<<endl;
    echo_data d2{d1}; //copy construtor shall call. not clear if copy constructor of echo_data is not defined , 
                      //then coordinates copy constructor is called , if deined then normal constructor is called ?

    //Where all copy called 
    /*
    Most surprising / dangerous copies
   ↓
    5. catch (Type e) by value
    4. throw expr;  (copy of thrown object)
    3. Parameter of type std::function<T>
    2. Returning big object from getter (T getX() const)
    1. Adding many elements to vector → reallocation
    ↓
    Least surprising
    */ 
    return 0;
}
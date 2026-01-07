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
};

class echo_data{
    vector<coordinates> d{10};
    char *dp = "data_point1";
public:
    string get_dp_name(){
        return dp;
    };
    //default constructor 
    echo_data(){
        cout<<"construtor echo_data"<<endl;
    }
    //default assignment 
};


int main(void){
    echo_data *data1 = new echo_data();
    echo_data *data2 =data1; //here constructor is not called will see where all copy constructor is called
    return 0;
}
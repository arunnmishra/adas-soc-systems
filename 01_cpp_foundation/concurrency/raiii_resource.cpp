#include<iostream>
#include<vector>
#include<memory>

using namespace std;

class mapObject{
    vector<int> obj;               
    string mapper_name;
    unique_ptr<char[]> map_buff;    //rule of 0 can apply because we use unique_ptr, string and vector
public:
    mapObject(string s):mapper_name{s}{
        cout<<"map object constructed!!"<<endl;
    }
    char * get_map_buff() const{
        return map_buff.get();       //Best. Either get a raw pointer , ownership not trnasfered. caller can modify, most cases 
        //return map_buff;            //return the unique_ptr 
        //return move(map_buff);    // ownership transfer, destructive getter
    }
    string get_mapper_name() const{
        return mapper_name;
    }

    void set_mapper_name(const string &N){ // not so good API in modern CPP, const blocks move
        mapper_name = N;
    }
    void set_mapper_name1( string N){ // modern best practice , why ?
        mapper_name = move(N);
    }

};

int main (void){
    mapObject M1("First Mapper");
    char * map_buff_ref = M1.get_map_buff(); //const reference for access 
    cout<<M1.get_mapper_name()<<endl;
    cout<<"--------------------------------"<<endl;
    M1.set_mapper_name("1st Mapper");
    cout<<"--------------------------------"<<endl;
    M1.set_mapper_name1("1st Mapper");


    return 0;
}
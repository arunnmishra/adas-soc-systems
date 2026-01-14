#include<iostream>
#include<vector>
#include<memory>

using namespace std;

class mapObject{
    vector<int> obj;
    string mapper_name;
    unique_ptr<char> map_buff;
public:
    mapObject(string s):mapper_name{s}{
        cout<<"map object constructed!!"<<endl;
    }
    unique_ptr<char> get_map_buff() const{
        return map_buff;
    }
    string get_mapper_name() const{
        return mapper_name;
    }

};

int main (void){
    mapObject M1("First Mapper");
    cout<<M1.get_mapper_name()<<endl;
    return 0;
}
#include<iostream>
#include<vector>
#include<memory>

using namespace std;

//modern embedded cpp design have custom pool with RAII owbership 

//define the memory pool TODO :: define a proper custom pool
class custom_pool{

public:
    void * allocate(size_t s){
        cout<<"allocated: "<<s<<" bytes."<<endl;
        return new char(s);
    };
    void  deallocate(void * p){
        cout<<"deallocated: "<<p<<endl;
        delete p;  
    };
};

//we want to use this pool with unique pointer (RAII), so we need to define custom delter 
void deleter(char *p){
    delete p;
}

//OR :: TODO define a deleter 
struct pooldeleter{
    custom_pool *pool;
    void operator()(char *p)const{
        pool->deallocate((void *)p);
    }
}


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
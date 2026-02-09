#include <new>
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <span>


//Non-Owning Access to existing memory with explicit bounds

template<typename T>
void display_data(std::span<T> d)
{
    std::cout<<"Viewing data. Modification not allowed"<<std::endl;
    for(auto i: d){
        std::cout<<i<<std::endl;
    }
}

int main() {
    std::vector<int> messages{1,2,3,4};
    std::string raw_array[] = {"I", "Love", "India"};

    std::cout<<"===== Look at vector ======"<<std::endl;
    display_data<int>(messages);

    std::cout<<"===== Look at Array ======"<<std::endl;
    display_data<std::string>(raw_array);
    
    return 0;
}

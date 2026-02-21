#include <new>
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <optional>


/*
// C++17 style – "maybe value"
std::optional<Data>        try_read();     // since C++17

// C++23 style – "value or explicit error"
std::expected<Data, Error> try_read();     // since C++23

// Custom / non-standard (still very popular)
result<Data, std::error_code> read();      // not in std::
*/

struct data{
    int position;
    char status;
};

std::optional<data> result(int a){
   if(a>10){
        data d1{a,'O'};
        return d1; 
    }
}

int main() {
    std::cout<<"===== Optional return ======"<<std::endl;
    auto r = result(12);
    if(r){
        std::cout<<"Got the result"<<std::endl;
    }
    return 0;
}

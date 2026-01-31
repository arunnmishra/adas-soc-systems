#include <new>
#include <memory>
#include <iostream>
#include <vector>
#include <string>

using namespace std::string_literals;

struct Msg {
    int id;
    Msg(int i=0):id{i}{
        std::cout<<"Msg constructed"<<std::endl;
    }
    ~Msg(){
        std::cout<<"Msg destructed"<<std::endl;
    }
    Msg(const Msg &other){
        id = other.id;
        std::cout<<"Msg copy constructed"<<std::endl;
    }
    Msg(Msg &&other) noexcept { //move constructor will be used by stl only if noexcept
        id = other.id;
        std::cout<<"Msg move constructed"<<std::endl;
    }
};

void log(const std::string& s){
    std::cout<<"Lvalue log: "<<s<<std::endl;
}
void log(std::string&& s){
    std::cout<<"Rvalue log: "<<s<<std::endl;
}

template<typename T>
void wrapper(T&& s) {
    log(s);    // perfect forwarding
}

int main() {
    std::vector<Msg> messages;
    messages.reserve(2);              // Pre-allocate memory
    std::cout<<"--- Push Back---"<<std::endl;
    messages.push_back(Msg{1});       // Move construction
    std::cout<<"--- Emplace Back---"<<std::endl;
    messages.emplace_back();          // Default construction
    std::cout<<"--- End ---"<<std::endl;
    
    std::cout<<"--- Test Perfect forwarding ---"<<std::endl;
    std::string a = "hello";
    wrapper(a);
    wrapper("world"s);
    return 0;
}

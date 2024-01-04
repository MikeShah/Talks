/// @file functional.cpp
/// g++ -std=c++20 functional.cpp -o prog && ./prog 
#include <iostream>
#include <string>
#include <functional>

struct Actor{ 
    public:
    Actor(std::string name) : mName(name){}
    const std::string mName;
};

/// Higher-order function
void Agenda(std::function<void(const Actor&)> f, const Actor& a){

    // Call function with the actor argument
    f(a);
}

int main(){
    
    // Define a lambda function (Implemented as a 'functor' behind the scenes)
    auto practice = [](const Actor& s){
        std::cout << s.mName << " ::practice()\n";
    };
    auto dance    = [](const Actor& s){
        std::cout << s.mName << " ::dance()\n";
    };

    // Instantiate data
    Actor a = Actor("Mike");

    // Pass function as a parameter
    Agenda(practice, a);
    Agenda(dance, a);

    return 0;
}   

/// @file functional_visitor.cpp
/// g++ -std=c++20 functional_visitor.cpp -o prog && ./prog 
#include <iostream>
#include <string>
#include <variant>

/// In this example we reduce our 'classes' to simple structs with minimal
/// data.
struct MethodActor{ 
    public:
    MethodActor() = default;
    MethodActor(std::string name){
    }
    const std::string mName;
};

struct ClassicalActor{
    public:
    ClassicalActor() = default;
    ClassicalActor(std::string name){
    }
    const std::string mName;
};

/// Note: Does not have to be globally scoped
using Actor = std::variant<MethodActor, ClassicalActor>;

/// Create a 'visitor' that handles the cases for each type in the variant
struct PracticeVisitor{
    void operator()(const MethodActor& a) const{
        std::cout << "Practicing like a Method Actor\n";
    }
    void operator()(const ClassicalActor& a) const{
        std::cout << "Practicing like a Classical Actor\n";
    }
};

int main(){
    
    // Define a lambda function (Implemented as a 'functor' behind the scenes)
    auto practice = [](std::string s){
        std::cout << s << "::Practice()\n";
    };

    // Create a variant -- effectively holding one type or the other in a 'tagged union'
    Actor a = MethodActor("Mike");

    // Grab the data that we need based on the type in the variant
    std::visit(PracticeVisitor{}, a);  

    return 0;
}   

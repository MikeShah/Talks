/// @file functional_visitor.cpp
/// g++ -std=c++20 functional_visitor.cpp -o prog && ./prog 
#include <iostream>
#include <string>
#include <variant>

/// In this example we reduce our 'classes' to 
/// simple structs with minimal behaviors
struct MethodActor{ 
    public:
    MethodActor() = default;
    MethodActor(std::string name) : mName(name){}
    const std::string mName;
};

struct ClassicalActor{
    public:
    ClassicalActor() = default;
    ClassicalActor(std::string name): mName(name) {}
    const std::string mName;
};

/// Note: Does not have to be globally scoped
using Actor = std::variant<MethodActor, ClassicalActor>;

/// Create a 'visitor' that handles the cases for 
/// each type in the variant
struct PracticeVisitor{
    void operator()(const MethodActor& a) const{
        std::cout << "Practicing like a Method Actor\n";
    }
    void operator()(const ClassicalActor& a) const{
        std::cout << "Practicing like a Classical Actor\n";
    }
};

int main(){

    // Create a variant -- effectively holding one type or 
    // the other in a 'tagged union'
    Actor a = MethodActor("Mike");
    // Grab the data that we need based on the type in the variant
    std::visit(PracticeVisitor{}, a);  

    Actor b = ClassicalActor("Shah");
    std::visit(PracticeVisitor{}, b);  

    return 0;
}   

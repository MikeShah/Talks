/// @file interface.cpp
/// g++ -std=c++20 interface.cpp -o prog && ./prog 
#include <iostream>
#include <string>

/// Serves as an 'interface' for the 'Base class'
/// Can force functionality to be implemented
class IActor{
    public: // Access Specifier (information hiding modifiers)

        IActor(std::string name) : mName(name){ }
        virtual ~IActor(){ }

        /// Purely virtual function -- i.e. it must be implemented in derived class
        virtual void Practice() = 0;

    private: 
        // Data associated with the 'Actor'
        std::string mName;
};

class MethodActor : public IActor{
    public:
    MethodActor(std::string name) : IActor(name){
    }
    /// NOTE: Should mark functions with 'override' to ensure that you are in fact
    ///       overriding the purely virtual function.
    void Practice() override{
        std::cout << "MethodActor::Practice()\n";
    }
};

class ClassicalActor : public IActor{
    public:
    ClassicalActor(std::string name) : IActor(name){
    }
    /// NOTE: Should mark functions with 'override' to ensure that you are in fact
    ///       overriding the purely virtual function.
    void Practice() override{
        std::cout << "ClassicalActor::Practice()\n";
    }
};


int main(){
    
    MethodActor* s = new MethodActor("Golshifteh Farahani");
    s->Practice();

    delete s;
    return 0;
}   

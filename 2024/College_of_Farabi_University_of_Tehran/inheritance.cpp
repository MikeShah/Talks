/// @file inheritance.cpp
/// g++ -std=c++20 inheritance.cpp -o prog && ./prog 
#include <iostream>
#include <string>

class Actor{
    public: // Access Specifier (information hiding modifiers)

        Actor(std::string name) : mName(name){ }
        /// Note: Destructor needs to be marked 'virtual' in inheritance, such
        ///       to ensure that it is called from derived classes.
        virtual ~Actor(){ } 
        void PrintName(){
            std::cout << "Actor mName=" << mName << std::endl;
        }
    private: 
        // Data associated with the 'Actor'
        std::string mName;
};

/// - A new 'derived type' from 'Actor' (Actor serves as the Base class)
/// - Inherits 'public' functionality of Actor class
/// - Is a 'type of' Actor.
/// - Can expand on the functionality of 'Actor'
class MethodActor : public Actor{
    public:
    MethodActor(std::string name) : Actor(name){
    }
    void PracticeMethod(){
        std::cout << "MethodActor::PracticeMethod()\n";
    }
};


int main(){
    
    MethodActor* s = new MethodActor("Golshifteh Farahani");
    s->PrintName();
    s->PracticeMethod();

    delete s;
    return 0;
}   

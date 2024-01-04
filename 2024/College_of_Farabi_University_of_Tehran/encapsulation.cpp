/// @file encapsulation.cpp
/// g++ -std=c++20 encapsulation.cpp -o prog && ./prog 
#include <iostream>
#include <string>

class Actor{
    public: // Access Specifier (information hiding modifiers)

        // Constructor - action performed creating object
        Actor(std::string name) : mName(name){

        }

        /// Destructor - action performed on destruction 
        ///              (i.e. leaving scope, or explicitly deleted).
        ///              Not explicitly called otherwise.
        ~Actor(){
        }

        /// A public member function that acts on a specific instance
        /// of an object.
        void PrintName(){
            std::cout << "Actor mName=" << mName << std::endl;
        }

    private: 
        // Data associated with the 'Actor'
        std::string mName;
};


int main(){
    Actor s("Golshifteh Farahani");
    s.PrintName();

    return 0;
}   

// @file mikepointer.cpp
// g++ -std=c++17 mikepointer.cpp -o prog
#include <iostream>

// WARNING: NOT PRODUCTION CODE
//          Just a sketch for a talk :)
//          Please use built-in smart pointers
template <class T>
class MikeSafePointer{
public: 
    MikeSafePointer(){
        rawPointer = new T;
        use_count = 1; // Consider an 'addUse'
    }                  // and 'Release' function
                       // to manage this value.
    // Destructor checks if it's safe to destroy
    ~MikeSafePointer(){
        if(1==use_count){
            delete rawPointer;
            rawPointer = nullptr;
        }else{
            // Maybe log a warning if in DEBUG mode
        }
    }

private: 
    // Hide the raw pointer (even better use pIMPL*)
    T* rawPointer;
    int use_count; // Increment every time something is assigned
                   // to this pointer.
                   // i.e., this could be the 'ref count'
};

int main(){

    MikeSafePointer<int> mike_int_pointer;

    return 0;
}


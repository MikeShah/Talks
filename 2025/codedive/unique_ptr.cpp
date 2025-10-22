// @file: unique_ptr.cpp
#include <iostream>
#include <memory> // unique_ptr

// Unique pointer will take advantage of RAII, 
// and be destroyed when it is no longer in scope,
// or otherwise used.
class UDT{
    public:
        // Constructor (called on creation)
        UDT() { std::cout << "UDT Created" << std::endl; }
        // Destructor (called on destruction)
        ~UDT() { std::cout << "UDT Destroyed" << std::endl; }
};

// Functor that is called and deletes our 'int_ptr'
struct IntDeleter{
    void operator()(int* int_ptr){
        std::cout << "IntDeleter called" << std::endl;
        delete int_ptr;
    }
};

int main(){

	UDT u;
    std::unique_ptr<int,IntDeleter> my_ptr(new int);

    return 0;
}

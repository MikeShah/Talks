// @file: dynamic_cast.cpp
// g++ -std=c++23 dynamic_cast.cpp -o prog
#include <print>

// Base class
struct Base {
	Base(){}
    virtual ~Base(){}
};

// a wider interface
struct Derived : Base {
	Derived(){}
	virtual ~Derived(){}
};

int main(){

//	Base* base = new Base;
	Base* base = new Derived;

	
    if (Derived* pd = dynamic_cast<Derived*>(base)) {
		// Should tkae this path
		std::println("cast to derived successfully");
    }else {
		// Uncommenting line 23 should take this path
		std::println("Base class");
    }

	return 0;
}

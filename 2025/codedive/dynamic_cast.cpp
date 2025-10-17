// @file: dynamic_cast.cpp
// g++ -std=c++23 dynamic_cast.cpp -o prog && ./prog
#include <print>
class Base { 
    virtual void someFunction() { std::println("Base::someFunction");
    } 
};
class Derived: public Base { 
    int a; 
    public:
    virtual void someFunction() override { std::println("Derived::someFunction");    } 

    virtual void DoAction(){ std::println("Derived::DoAction"); }
};

void myFunction(Base* b){
    if(dynamic_cast<Derived*>(b)){  /* is this valid */  }
}

int main(){
    // If 'object' is a complete type for 'Derived' then we can cast.
    Base* object  = new Derived;          
    Derived* D  = new Derived;       

    if(dynamic_cast<Derived*>(object)){         
         std::println("this works!!");
         static_cast<Derived*>(object)->someFunction();
         static_cast<Derived*>(object)->DoAction();
    }
}


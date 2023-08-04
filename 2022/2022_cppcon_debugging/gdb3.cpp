// g++ -g -Wall -Wextra -std=c++17 gdb3.cpp -o gdbexample3
#include <iostream>

class Animal{
    public:
    Animal(){ std::cout << "Animal Constructor"; }
    virtual ~Animal(){}

    virtual void action(){
       std::cout << "Animal::action()"; 
    }
};

class Dog : public Animal{
    public:
    Dog(){
       std::cout << "Dog Constructor"; 
    }
    void action(){
       std::cout << "Dog::action()"; 
    }
};

int main(){

    Animal* genericAnimal;
    genericAnimal = new Dog;
    // What will happen here?
    genericAnimal->action();
    // How about after this
    delete genericAnimal;
    // Try 'whatis' in gdb
    genericAnimal = new Animal;
    genericAnimal->action();

    return 0;
}

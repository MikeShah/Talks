// @file sharing.cpp
// g++ -std=c++17 sharing.cpp -o prog
#include <iostream>
#include <string>
// Custom data structure
struct Person{
    std::string nickname;
    /* ... assume more attributes */
};
struct Company{
    Person* ceo; // The employees
};
struct Friends{
    Person* friend1; // Only 1 friend for simplicity...
};
int main(){
    // Create 'me' with some attributes
    Person michael;
    michael.nickname = "Michael";
    // ... Create other objects
    Person* myFakeTwinBrother;
    Company myEmployer; 
    Friends myFriends;
    // For each of these other objects,
    // share some data
    myFakeTwinBrother = &michael;
    myEmployer.ceo = &michael;
    myFriends.friend1 = &michael;
    // Hmm, I've decided to change my nickname.
    michael.nickname = "Mike";
    // Let's confirm our pointers update
    std::cout << "MyFakeTwinBrother also is   : " << (*myFakeTwinBrother).nickname << std::endl;
    std::cout << "MyFakeTwinBrother is still  : " << myFakeTwinBrother->nickname << std::endl;
    // ^ Note the new syntax with the arrow, which derefences a field in a struct/class
    std::cout << "My employer should call me  : " << myEmployer.ceo->nickname << std::endl;
    std::cout << "My my friend should call me : " << myFriends.friend1->nickname << std::endl;

    return 0;
}



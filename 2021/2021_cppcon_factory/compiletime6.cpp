// @file compiletime6.cpp
// g++ -std=c++17 compiletime6.cpp
#include <vector>

class ObjectType1{
    public:
    ObjectType1(){}
    ObjectType1(int x,int y){ // do some work
                            }
};

class ObjectType2{};

// Create your units ahead of time.
std::vector<ObjectType1> units1;
std::vector<ObjectType2> units2;

// Try to handle creation of objects here
void makeObject(int objectType,
                int param1,
                int param2){
    if(1 == objectType){ 
        ObjectType1 newObject(param1,param2);
        units1.push_back(newObject);
    }
    if(2 == objectType){ 
        ObjectType2 newObject;
        units2.push_back(newObject);
    }
}


int main(){

    makeObject(1,0,0);
    makeObject(1,10,20);
    // Look different object types!
    makeObject(2,10,20);

    // ...
    while(true){
        // Run your game here

        // Iterate through your units
        // update them, run logic, etc.
    }

    return 0;
}

// @file compiletime5.cpp
// g++ -std=c++17 compiletime5.cpp
#include <vector>

class ObjectType1{
    public:
    ObjectType1(){}
    ObjectType1(int x,int y){ // do some work
                            }
};

class ObjectType2{};

// Try to handle creation of objects here
void makeObject1AndPushToVector(std::vector<ObjectType1>& units1Vector,
                                int x,
                                int y){
    ObjectType1 newObject(x,y);
    units1Vector.push_back(newObject);
}


int main(){

    // Create your units ahead of time.
    std::vector<ObjectType1> units1;
    std::vector<ObjectType2> units2;

    // Wait, which constructor do I use?
    makeObject1AndPushToVector(units1,0,0);
    makeObject1AndPushToVector(units1,10,20);
    // ...
    while(true){
        // Run your game here

        // Iterate through your units
        // update them, run logic, etc.
    }

    return 0;
}

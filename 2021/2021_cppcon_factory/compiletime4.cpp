// @file compiletime4.cpp
// g++ -std=c++17 compiletime4.cpp
#include <vector>

class ObjectType1{};
class ObjectType2{};
class ObjectType3{};

int main(){

    // Create your units ahead of time.
    std::vector<ObjectType1> units1;
    std::vector<ObjectType2> units2;
    std::vector<ObjectType3> units3;


    while(true){
        // Run your game here

        // Iterate through your units
        // update them, run logic, etc.
    }

    return 0;
}

// @file compiletime2.cpp
// g++ -std=c++17 compiletime2.cpp

class ObjectType1;
class ObjectType2;
class ObjectType3;

int main(){

    // Create your units ahead of time.
    ObjectType1* units1 = new ObjectType1[100];
    ObjectType2* units2 = new ObjectType2[100];
    ObjectType3* units3 = new ObjectType3[100];


    while(true){
        // Run your game here

        // Iterate through your units
        // update them, run logic, etc.
    }
    delete[] units1; 
    delete[] units2;
    delete[] units3;

    return 0;
}

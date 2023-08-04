// @file compiletime3.cpp
// g++ -std=c++17 compiletime3.cpp

struct ObjectType1{};
struct ObjectType2{};
struct ObjectType3{};

// Delete old array and copy in data
ObjectType1* ResizeObjectType1(ObjectType1* array,
                               size_t oldsize,
                               size_t newsize)
{
    ObjectType1* newArray = new ObjectType1[newsize];
    for(size_t i=0; i < oldsize; i++){
        newArray[i] = array[i];
    }
    delete[] array;
    return newArray;
}

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

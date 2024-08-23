// @file rangedfor.cpp
// Compile and run: g++ -std=c++23 rangedfor.cpp -o prog && ./prog
#include <print>
#include <vector>

struct Student{
    long mID;
    long mGrade;
};

int main(){

    // Use initializer list to populate vector.
    // Explicitly supply the 'type' so we don't interpret as a 'pair'
    std::vector<Student> students = {{123,100},
                                     {124,99}};

    // The '&' is important in the ranged-for loop so that we do not
    // make a 'copy'. Generally for types less than size of a pointer
    // on your architecture this matters.
    // Note -- you can still break out of loops if needed.
    for(auto& elem : students){
        std::println("{} - {}",elem.mID, elem.mGrade);
    }

    return 0;
}

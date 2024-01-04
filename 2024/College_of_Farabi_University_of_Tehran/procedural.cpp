/// @file procedural.cpp
/// g++ -std=c++20 procedural.cpp -o prog && ./prog 
#include <iostream>

// constants represented as 'integers' types
enum SHAPE{SQUARE, CIRCLE, PENTAGON, END};

// Strongly typed, and scoped -- no type conversions
enum class STATE{RUNNING, OFF, PAUSED, ERROR};

// aggregate data type
struct PieceOfData{
    int id;
    char letter_grade;
    float grade_point_average;
};

// Special class type holding one data member at a time.
// Space allocated for largest type, and byte-aligned on architecture.
union Event{
    // Note: 'type' always first member to ensure we can record state event
    int type;
    // Observe that we can 'nest' types to scope them.
    struct mouse_event{
        int type;
        bool left;
        bool middle;
        bool right;
    };
    struct key_event{
        int type;
        char states[255];
    };
};

void function(SHAPE s){
    if(s==SQUARE){

    }else if(s==CIRCLE){
        std::cout << "Circle!\n";
    }else{
    }
}

void function(STATE s){
    /// Switch statement -- note: compile with -Wall in case you
    ///                           miss a state!
    switch(s){
        case STATE::RUNNING:
            std::cout << "Running\n";
            break;
        case STATE::PAUSED:
        case STATE::OFF:
        case STATE::ERROR:
        default:
            break;
    }
}

int main(){


    function(CIRCLE);
    function(STATE::RUNNING);

    return 0;
}   

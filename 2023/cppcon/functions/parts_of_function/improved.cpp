// parts_of_function/impproved.cpp
#include <iostream>
#include <string>

enum class RESULT{FAILED_TO_LOAD=-1,LOAD_SUCCESS=0};

RESULT LoadBitmapFile(std::string image){
    RESULT result = RESULT::FAILED_TO_LOAD;
    
    // ...Load file logic here ...

    return result;
}

int main(int argc, char* argv[]){

    return 0;
}

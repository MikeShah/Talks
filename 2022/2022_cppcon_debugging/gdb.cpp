// g++ -g -Wall -Wextra -std=c++17 gdb.cpp -o gdbexample
#include <iostream>
#include <vector>
#include <string>

struct object{
    int field1;
    int field2;
};

void otherhelper(){

    int* p = nullptr;
    *p = 10;
}

void helper(){
    otherhelper();

    int* x= nullptr;
    int* p=x;

    *p = 42;
}



int main(){

    object o1;
    o1.field1 = 7;
    o1.field2 = 9;

    std::vector<std::string> strings;

    for(int i=0; i < 10; i++){
        strings.push_back(std::to_string(i));
    }

    for(std::vector<std::string>::iterator it = strings.begin(); 
        it != strings.end(); it++){
        std::cout << *it << std::endl;
        
    }

    helper();

    int counter =0;
    while(1){
        std::cout << "running " << counter << " times\n";
        counter++;
    }

    return 0;
}

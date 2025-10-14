// @file: raii.cpp
// g++ raii.cpp -o prog && ./prog
#include <iostream>
#include <fstream>

struct FileScoped{
    FileScoped(const char* filename){
      mFile.open(filename);
    }
    ~FileScoped(){
      mFile.close();
    }
    std::fstream mFile;
};
struct NewIntScoped{
    NewIntScoped(std::size_t size){
       mIntPointer = new int[size];
    }
    ~NewIntScoped(){
      delete[] mIntPointer;
    }
    int* mIntPointer;
};

void foo(){
    FileScoped f("data.txt");
    NewIntScoped ptr(50);
} // File closed, and heap memory freed

int main(){
    foo();
    return 0;
}

// @file: wc98.cpp
// @description: The purpose of this file is to read the
//               number of words in a file.

// Compile: g++ -g -Wall -std=c++98 wc98.cpp -o wc98
// Run:     ./wc98 wc98.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct wcInfo{
    size_t bytes;
    size_t lines;
    size_t words;
    // 0-initialize everything in constructor
    wcInfo(){
        bytes=0;
        lines=0;
        words=0;
    }
};

/// Helper function for returning file size
size_t GetFileSize(const char* filename){
    std::ifstream myFile(filename, std::ios::ate | std::ios::in | std::ios::binary);
    return myFile.tellg();
}

/// Main function for retrieving the file size 
wcInfo wc(const char* filename){
    wcInfo result;     

    // Open file for input
    std::ifstream myFile(filename,std::ios::in);
    
    // Iterate through each line and each word
    // using stringstream to parse 'whitespace'
    if(myFile.is_open()){
        result.bytes = GetFileSize(filename);
        std::string line;
        while(std::getline(myFile,line)){
            ++result.lines;
            std::stringstream s(line);
            std::string word;
            while(s >> word){
                ++result.words;
            }
        }
    }else{
        std::cerr << "File could not be read: " << filename << std::endl;
    }

    return result; 
}

/// Program entry point
int main(int argc, char* argv[]){

    // Test program arguments prior to usage 
    if(argc < 2){
        std::cerr << "Usage: ./prog filename" << std::endl;     
    }else{
        wcInfo results = wc(argv[1]);
        std::cout <<                  "\t"
                  << results.lines << "\t"
                  << results.words << "\t"
                  << results.bytes << "\t" << std::endl;
    }

    return EXIT_SUCCESS;
}

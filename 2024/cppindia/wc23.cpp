// @file: wc23.cpp
// @description: The purpose of this file is to read the
//               number of words in a file.

// Compile: g++ -g -Wall -std=c++20 wc23.cpp -o wc23
// Run:     ./wc23 wc23.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

struct wcInfo{
    size_t lines{0};
    size_t words{0};
    size_t bytes{0};
};

/// Main function for retrieving the file size 
wcInfo wc(const char* filename){
    wcInfo result{};     
    // Open file for input
    std::ifstream myFile(filename,std::ios::in);
    
    // Helper function for words in line
    auto wordsInLine = [](auto line){
            size_t count{};
            std::stringstream s(line);
            std::string word{};
            while(s >> word){
                ++count;
            }
            return count;
    };

    // Iterate through each line and each word
    // using stringstream to parse 'whitespace'
    if(myFile.is_open()){
        result.bytes = std::filesystem::file_size(filename);
        std::string line{};
        while(std::getline(myFile,line)){
            ++result.lines;
            result.words += wordsInLine(line);
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
        // structured binding 
        auto[lines, words, bytes] = wc(argv[1]);
        std::cout <<                  "\t"
                  << lines << "\t"
                  << words << "\t"
                  << bytes << "\t" << std::endl;
    }

    return EXIT_SUCCESS;
}

// @file: wc23_1.cpp
// @description: The purpose of this file is to read the
//               number of words in a file.

// Compile: g++ -g -Wall -std=c++23 wc23_1.cpp -o wc23_1
// Run:     ./wc23_1 wc23_1.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <print>

std::tuple<size_t,size_t,size_t> wc(const char* filename){
    size_t lines{};
    size_t words{};
    size_t bytes{};
    // Open file for input
    std::ifstream myFile(filename,std::ios::in);
    
    // Helper lambda function for counting words in line
    auto wordsInLine = [lines](auto line){
            std::stringstream s(line);
            std::string word{};
            while(s >> word){
                ++lines;
            }
    };

    // Iterate through each line and each word
    // using stringstream to parse 'whitespace'
    if(myFile.is_open()){
        bytes = std::filesystem::file_size(filename);
        std::string line{};
        while(std::getline(myFile,line)){
            ++lines;
            words += wordsInLine(line);
        }
    }else{
        std::cerr << "File could not be read: " << filename << std::endl;
    }

    return std::make_tuple<size_t,size_t,size_t>(lines,words,bytes); 
}

/// Program entry point
int main(int argc, char* argv[]){

    // Test program arguments prior to usage 
    if(argc < 2){
        std::cerr << "Usage: ./prog filename" << std::endl;     
    }else{
        // structured binding 
        auto[lines, words, bytes] = wc(argv[1]);
        std::println("\t{}\t{}\t{}",lines,words,bytes);
    }

    return EXIT_SUCCESS;
}

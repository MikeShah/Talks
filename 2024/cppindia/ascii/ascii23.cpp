// @file: ascii98.cpp
// @description: The purpose of this file is to convert an image to an
//               ascii rendering on the terminal.

// Compile: g++ -g -Wall -std=c++98 ascii98.cpp -o ascii98
// Run:     ./ascii98 ascii98.cpp
// Run with gdb: gdb ./prog --tui


#include <iostream>     // For general I/O
#include <string>       // std::string data type
#include <vector>       // std::vector data type
#include <fstream>      // Useful for opening files
#include <span>         // For passing data around
#include <algorithm>    // For 'for_each'>
#include <execution>    // For parallel execution policy
#include <iterator>     // Compute distance for idx (between iterators)
#include <numeric>

// Image dimensions
// Recall: Anything in C++ that begins
//         with a '#' sign is read in by
//         the preprocessor before compiling
//         our code.
#define WIDTH 294   // How 'wide' the image is in pixels
#define HEIGHT 251  // How 'high' the image is in pixels
#define CHANNELS 3  // 3 Channels, (R)ed, (G)reen, (B)lue.
   
// The 'brightness' string is  is a series of 
// total of 65 characters. The characters are 
// arranged from 'least bright' to 'most bright' 
// when generating an ASCII representation of an image.
// You are welcome to adjust this string as you see fit
// if you think you can generate a better image.
const std::string brightness = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

/* LoadPPMImage 
 * Input: filename
 *
 * This function loads up a PPM Image. PPM Images
 * can be generated from programs like GIMP 2.0 for
 * free.
 *  
 * The goal is to be able to 'parse' or read in this file 
 * and store the red, green, and blue values, and output
 * the values into a vector.
 *
 * Lines that start with a '#' can be ignored.
 */
std::vector<uint8_t> LoadPPMImage(const std::string filename){
    // Storage of pixels.
    std::vector<uint8_t> pixels;

    std::ifstream myFile(filename);
    if(myFile.is_open()){
        // Read in each character or line
        std::string line;
        bool dimensionsNext{false};
        while(std::getline(myFile,line)){
            if(line[0]=='#'){
                std::cout << "ignoring: " <<line << '\n';
                continue;
            }else if(line=="P3"){ 
                std::cout << "format:" <<line << '\n';
                dimensionsNext=true;
                continue;
            }else if(dimensionsNext==true){
                std::cout << "width,height =" << line << std::endl;
                dimensionsNext=false;
                // TODO: read in next dimension for the range
                std::getline(myFile,line);
            }else{
                pixels.push_back(std::stoi(line));
            }

        }
        myFile.close();
    }

    return pixels;
}

/* ConverPixelsToGray
 * Input: Vector of RGB Pixels
 *
 * Takes in a vector of RGB pixels and converts them to a single 
 * gray value.
 * e.g.
 * RGB RGB RGB (The 'average' value of RGB maps to a single G value)
 * G G G
 */
std::vector<uint8_t> ConvertPixelsToGray(std::span<uint8_t> pixels){
    std::vector<uint8_t> result(WIDTH*HEIGHT);
    result.reserve(WIDTH*HEIGHT);
    // Populate with values 0 to the size 
    std::iota(result.begin(),result.end(),1);

    std::for_each(result.begin(),result.end(),[&](auto idx){
        float r = (float)pixels[3*idx]*0.21;
        float g = (float)pixels[3*idx+1]*0.72;
        float b = (float)pixels[3*idx+2]*0.07;
        float avg = (float)(r+g+b)/3.0;
        result[idx] = avg;
    });

    return result;
}

/* MapValueToIndex 
 * (Helper Function)
 * You can create whatever helper functions you like for
 * this assignment, but I used this one (and the other provided
 * functions) in my solution.
 *
 * The goal is to take in your 'brightness string' and then 
 * 'map' a value from 0-255 (your grayscale pixel) to a value
 * between 0 and 64(i.e. each individual character in 
 * your 'brightness string').
 *
 * This will be useful when printing out your characters to
 * the terminal.
 */
char MapValueToIndex(std::string_view chars, uint8_t value, uint8_t start, uint8_t end){
    // Figure out the range
    float nextChar = (end-start)/(float)chars.size();
    // Figure out the next character in lookup
    int index = (float)value/nextChar;
    // Return the character
    return chars[index];
}

/* PrintPixelsAsChar
 * Input: vector of grayscale pixel values
 * This function will iterate through the
 * pixel values and print out one character at a time
 * for the WIDTH of an image. Then move down to the next
 * row to print out the characters.
 *
 * The character printed out is a character that maps
 * to the 'brightness string' from the grayscale image.
 *
 */
void PrintPixelsAsChar(std::span<uint8_t> pixels){
    size_t counter=0;
    for(size_t y=0; y < HEIGHT; y++){
        std::cout << counter << "\t";
        ++counter;
        for(size_t x=0; x < WIDTH; x++){
            if(y==0){
                std::cout << '0';
                continue;
            }
            std::cout << MapValueToIndex(brightness,pixels[y*WIDTH+x],0,255);
        }
        std::cout << "\n";
    }
}

// Entry point of the program.
int main(int argc, char* argv[]){
 
    // The vector ppm will store the R,G,B pixel values of the PPM.
    std::vector<uint8_t> rgbPixels = LoadPPMImage("test.ppm");
    // The 'grayscale' pixels array converts the 'rgbPixels'
    // to grayscale pixels.
    // So if we have a bunch of pixels as such: 
    std::vector<uint8_t> grayscalePixels = ConvertPixelsToGray(std::span(rgbPixels));
    // PrintPixelsAsChar takes in the grayscale Pixels, maps the
    // pixels color to an ASCII character, and then outputs
    // those characters to the terminal.
    PrintPixelsAsChar(std::span(grayscalePixels));
  
    return 0; 
}

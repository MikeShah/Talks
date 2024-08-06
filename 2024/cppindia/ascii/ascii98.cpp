// @file: ascii98.cpp
// @description: The purpose of this file is to convert an image to an
//               ascii rendering on the terminal.

// Compile: g++ -g -Wall -std=c++98 ascii98.cpp -o ascii98
// Run:     ./ascii98 ascii98.cpp
// Run with gdb: gdb ./asci98 --tui


#include <iostream>     // For general I/O
#include <string>       // std::string data type
#include <vector>       // std::vector data type
#include <fstream>      // Useful for opening files

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
std::vector<unsigned char> LoadPPMImage(const std::string filename){
    // Storage of pixels.
    std::vector<unsigned char> pixels;

    std::ifstream myFile(filename);
    if(myFile.is_open()){
        // Read in each character or line
        std::string line;
        bool dimensionsNext = false;
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
std::vector<unsigned char> ConvertPixelsToGray(const std::vector<unsigned char>& pixels){
    std::vector<unsigned char> result;

    for(int i=0; i < WIDTH*HEIGHT*CHANNELS; i+=CHANNELS){
        float r = (float)pixels[i+0]*0.21;
        float g = (float)pixels[i+1]*0.72;
        float b = (float)pixels[i+2]*0.07;

        float avg = (float)(r+g+b)/3.0;

        result.push_back(avg);
    }

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
char MapValueToIndex(const std::string& chars, unsigned char value, unsigned char start, unsigned char end){
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
void PrintPixelsAsChar(const std::vector<unsigned char>& pixels){
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
    const std::vector<unsigned char> rgbPixels = LoadPPMImage("test.ppm");
    // The 'grayscale' pixels array converts the 'rgbPixels'
    // to grayscale pixels.
    // So if we have a bunch of pixels as such: 
    std::vector<unsigned char> grayscalePixels = ConvertPixelsToGray(rgbPixels);
    // PrintPixelsAsChar takes in the grayscale Pixels, maps the
    // pixels color to an ASCII character, and then outputs
    // those characters to the terminal.
    PrintPixelsAsChar(grayscalePixels);
  
    return 0; 
}

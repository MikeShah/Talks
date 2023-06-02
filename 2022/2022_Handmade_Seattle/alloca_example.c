// @file alloca_example.c
#include <stdio.h>  // printf
#include <stdlib.h> // alloca
#include <string.h> // strcpy
#include <ctype.h>  // toupper

void PrintUpperCase(char* nullTerminatedCharArray){

    // Allocate on the stack for a new mutated string
    // Add +1 for the null terminated character
    char* printName = (char*)alloca(strlen(nullTerminatedCharArray)+1);
    strcpy(printName,nullTerminatedCharArray);

    // Set the individual characters to uppercase
    size_t i=0;
    while(printName[i] != '\0'){
        printName[i] = toupper(nullTerminatedCharArray[i]);
        ++i;
    }

    // Print all at once the uppercase string with an endline
    printf("%s\n",printName);
}

// Entry point of program
int main(){

    // String literal allocated in static storage with \0 terminator
    PrintUpperCase("some string");

    return 0;
}



// @file alloca_big.c
#include <stdlib.h> // alloca


// Entry point of program
int main(){

    char* buffer = (char*)alloca(100000000);

    return 0;
}



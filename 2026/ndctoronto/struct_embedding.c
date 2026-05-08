// @file: struct_embedding.c
// Example simulating inheritance in C
// gcc -Wall -Wextra -g struct_embedding.c -o prog
#include <stdio.h>

typedef struct{
  int id;
  char* name;
}Player;

typedef struct{
  Player p;
  int magic;
}mage;

typedef struct{
  Player p;
  int power;
}hero;


int main(){

  return 0;
}

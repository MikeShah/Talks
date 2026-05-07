// @file: ooc_better.c
// gcc -Wall -Wextra -g ooc_better.c -o prog
//
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
/// Pointer should hold 'data' plus 'length'
typedef struct{
    int* array;
    int length;
}FatPointer;

/// Construct
FatPointer* IntArray_Make(int length){
  FatPointer* p = malloc(sizeof(FatPointer));
  p->array = malloc(sizeof(int)*length);
  p->length = length;
  
  return p;
}

/// Zero out the array (note: Could also use 'memset')
void IntArray_Zero (FatPointer* p){
  for (int i = 0; i < p->length; i++)
    p->array[i] = 0;
}

/// Print the array
void IntArray_Print (FatPointer* p){
  for (int i = 0; i < p->length; i++)
    printf ("array[%d]=%d\n", i, p->array[i]);
}

/// Increment range of values in an array
void IntArray_Increment (FatPointer* p, 
                         int start, int end, int increment){
  assert((end - start) <= p->length && "oops bounds error");
  for (int i = start; i < end; i++)
    p->array[i] += increment;
}

void IntArray_Free(FatPointer* p){
  free(p->array);
  free(p);
}

int main() {
  FatPointer* accounts = IntArray_Make(50);

  IntArray_Zero (accounts);
  IntArray_Increment (accounts, 0, 50, 5);
  IntArray_Print (accounts);

  IntArray_Free(accounts);

  return 0;
}



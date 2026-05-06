// @file: data.c
// gcc -Wall -Wextra -g data.c -o prog
//
#include <stdio.h>

/// Zero out the array (note: Could also use 'memset')
void
IntArray_Zero (int *array, int length)
{
  for (int i = 0; i < length; i++)
    array[i] = 0;
}

/// Print the array
void
IntArray_Print (int *array, int length)
{
  for (int i = 0; i < length; i++)
    printf ("array[%d]=%d\n", i, array[i]);
}

/// Increment range of values in an array
void
IntArray_Increment (int *array, int start, int end, int increment)
{
  for (int i = start; i < end; i++)
    array[i] += increment;
}

int
main ()
{

  int accounts[50];
  IntArray_Zero (accounts, 50);
  IntArray_Increment (accounts, 0, 50, 5);
  IntArray_Print (accounts, 50);

  return 0;
}

// @file: ooc.d
import std.stdio;

struct IntArray{
  int[50] array; // Always '50' for the sake of this example

  /// Zero out the array (note: Could also use 'memset')
  void Zero (){
    for (int i = 0; i < array.length; i++)
      array[i] = 0;
  }

  /// Print the array
  void Print(){
    for (int i = 0; i < array.length; i++)
      printf ("array[%d]=%d\n", i, array[i]);
  }

  /// Increment range of values in an array
  void Increment (int start, int end, int increment){
    for (int i = start; i < end; i++)
      array[i] += increment;
  }
}

int main() {
  IntArray accounts;
  accounts.Zero();
  accounts.Increment(0, 50, 5);
  accounts.Print();

  return 0;
}



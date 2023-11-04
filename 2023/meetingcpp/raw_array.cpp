// raw_array.cpp
#include <iostream>

int main(){

    // Fixed-size array at compile-time.
    // Contiguous chunk of memory for 9 integers
    // Total memory = 9 * sizeof(int) bytes
    int fixed_size_raw_array[9];

    // First element of allocation set to '15'
    fixed_size_raw_array[0] = 15;
    // Second element (offset of 1) set to '27'
    fixed_size_raw_array[1] = 21;
    // ...
    // Final element (offset of 8) set to 101.
    fixed_size_raw_array[8] = 101;


    // Dynamically allocate array at run-time.
    //  - We do this when we do not know the size
    //  - OR when the allocation is larger than can
    //       fit in stack memory.
    int* dynamic_allocation = new int[100000];

    // Similarly, we offset to element with brackets
    // operator to either read/write data.
    dynamic_allocation[99999] = 999999;

    // Dynamic allocations must be managed manually
    delete[] dynamic_allocation;

    return 0;
}

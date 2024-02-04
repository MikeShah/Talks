// @file introspection.d
import std.stdio;        // writeln
import core.stdc.stdlib; // malloc for manual allocation
import std.traits;       // hasMember

struct StructShallow{
    int* memory;
    uint elements;
}

struct StructDeepCopy{
    int* memory;
    uint elements;

    // Perform an actual copy an allocate to
    // new memory
    this(const ref StructDeepCopy rhs){
        // Free old memory
        if(memory!=null){
            free(memory);
        }
        elements = rhs.elements;
        memory = cast(int*)malloc(int.sizeof * elements);
        // Now perform copy
        // (Note: Could use memcpy here for optimization)
        foreach(i ; 0 .. elements){
            memory[i] = rhs.memory[i];
        }

    }
}

// Print out all of the data to see
// what type of copy was made.
// NEW: Templated function
// NEW: Introspection capabilities at compile-time
//      to ensure class has memory and elements fields.
void printData(T)(T theStruct)
    if(hasMember!(T,"memory") &&
       hasMember!(T,"elements"))
{
    foreach(i ; 0 .. theStruct.elements){
        write(theStruct.memory[i],",");
    }
    writeln();
}

// @file introspection.d
void main(){
    /////////// Shallow Copy ////////
    StructShallow s1;
    s1.elements = 10;
    s1.memory   = cast(int*)malloc(int.sizeof * s1.elements);
    // Assign elements some even numbers
    foreach(i ; 0 .. s1.elements){
        s1.memory[i] = i*2;
    }
    // Do a shallow copy.
    StructShallow s2 = s1;
    s2.memory[0] = 7;
    // Observe the problem here that we made a change in 
    // s2 above, but s1 is effected
    printData(s1);
    printData(s2);


    writeln();

    /////////// Deep Copy ////////
    StructDeepCopy s3;
    s3.elements = 10;
    s3.memory   = cast(int*)malloc(int.sizeof * s3.elements);
    // Assign elements some even numbers
    foreach(i ; 0 .. s3.elements){
        s3.memory[i] = i*2;
    }
    // Do a deep copy.
    StructDeepCopy s4 = s3;
    s4.memory[0] = 7;

    // Observe that these elements are now different because
    // the copy allocated new memory for our object.
    printData(s3);
    printData(s4);

}

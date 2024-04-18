// immutable.d
import std.stdio;

void main(){

    // ================= Immutable data and structure  =======================
    // Can always initialize data structure
    immutable int[] cannotChangeStructure = [1,2,3,4];
//    cannotChangeStructure ~= [1]; // Cannot change structure
//    cannotChangeStructure[0] = 5; // Cannot change values (immmutable int's)
    writeln(cannotChangeStructure);
    writeln("Can read values:" ,cannotChangeStructure[0]);

    // ================= Immutable data, with mutable data structure ==========
    // Can always initialize data structure
    // Can modify the data structure
    // But the 'data' is not modifyable
    immutable(int)[] canAppend = [1,2,3,4];

    canAppend ~= 1;     // Allowed to change data structure
//    canAppend[0] = 7; // Cannot change data

    writeln(canAppend);
}

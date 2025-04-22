// small.d
//
// Compile: dmd small.d -o prog
// Run: ./prog
//
// Compile & run: rdmd small.d

void main(){
	import std.stdio;

	writeln("Hello Yale!");
	writeln("I am a systems language -- look, pointers!");
	int x= 5;
	int* px = &x;

	writeln("Built-in data structures for 'python like' productivity");
	int[] data = [1,2,3,4,5];	// 'dynamic array'
	auto slice = data[1..3];	// A 'slice' of a dynamic array

	writeln(data);
	slice.writeln;	// Uniform Function Call Syntax for 'chaining' functions

	// 'Associative arrays' (maps/dictionray) as well!
	string[string] dictionary = ["dog":"goes bark","cat":"says meow"];
	writeln(dictionary);

	// 'struct' (value-type), and 'class' (reference-type) are available and
	// can be scoped.
	struct Vec3{
		float x,y,z;
	}
	// Compile-time reflection/introspection capabilities.
	static foreach(field ; Vec3.tupleof){
		pragma(msg,field.stringof);
	}
		
	// -- Other stuff --
	// Safety (initialized variables, garbage collection)
	// statically typed 
	// Threading and concurrency
	// Ranges instead of iterators
	// Lots of compile-time programming (no preprocessor, more type-safe)
	// And more!
}





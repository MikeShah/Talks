// Compile with: g++ -o prog library.cpp -ldl
//
// What is -ldl, well that is linking in the dynamic loading library of course!
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

typedef double(*double_double)(double);
int main(){
	// Here we get a pointer into our dynamically linked library
	void* handle;
	// Here we open up a specific library, in this case
	// the math library that already exists.
	handle = dlopen("/usr/lib/x86_64-linux-gnu/libm.so.6", RTLD_LAZY);
	// Output an error if we are not able to open our shared library
	// In our program, we will just exit
	if(!handle){
		std::cout << "Decide how you want to handle errors!\n";
		exit(1);
	}
	// This is what is known as a function pointer
	// It is a pointer to a named function, with the argument following
	// In this case, our function is called 'cosine', and it takes in a double.
	double (*cosine)(double);
	// We find our symbol in the library symbol table
	cosine = (double_double)dlsym(handle,"cos");
	// Actually use our function
	std::cout << "loaded cosine, and calculated cosine(45.0)=" << (*cosine)(45) << std::endl;
	// Finally we have to close access to our dynamic library
	// (Similar to how we always close files after opening them)
	dlclose(handle);
	return 0;
}

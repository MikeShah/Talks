// @file: cross_platform_example/example.cpp

#ifdef WINDOWS
	#include "Windows_Input_API.h"
#elif LINUX
	#include "Linux_Input_API.h"
#else
	static_assert(0,"Platform not supported");
#endif

int main(){
	return 0;
}


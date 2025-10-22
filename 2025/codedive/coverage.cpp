///////////////////////////////////////////////////////////////////////////////
// Compile with:  g++ -O0 -fprofile-arcs -ftest-coverage coverage.cpp -o prog//
//                Note I am turning off optimizations so no 'magic' compiler //
//                optimizations change our code for now. Additionally,       //
//                you see the test-coverage and profiling flags enabled.     //
//                                                                           //
// Run with:      ./prog                                                     //
//                                                                           // 
// After:         gcov prog-coverage.gcno 									 //
//                                                                           //
//                The above will use the gcov tool to provide an analysis of //
//                your file.                                                 //
//                                                                           //
// Finally:       cat coverage.cpp.gcov                                      //
//                                                                           //
//                Now you can see the results of your execution. You can     //
//                open up the file in vim or any other text editor if you    //
//                prefer.                                                    //
///////////////////////////////////////////////////////////////////////////////
#include <time.h>
#include <iostream>
#include <stdlib.h>

int main(){

	srand(time(NULL));

	int number =  (rand()%10) + 1;

	if(number>5){
		std::cout << number << " exectuted first branch\n";
	}else{
		std::cout << number << " exectuted second branch\n";
	}

	return 0;
}

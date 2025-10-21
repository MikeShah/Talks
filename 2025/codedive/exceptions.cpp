// @file: exceptions.cpp
// g++ -std=c++23 exceptions.cpp -o prog
#include <print>
#include <iostream>
#include <exception>
#include <expected> // std::logic_error exception

int main(){

	int i=0;
	std::cout << "Enter a positive value, or I'll throw an exception:";
	std::cin >> i;

	try{
		if(i==42){
			throw std::runtime_error("some type of exception");
		}else if(i < 0){
			// A more 'specific exception"
			// Perhaps 'invalid_argument' is a more useful exception?
			// Maybe we could handle this logic in code otherwise
			throw std::logic_error("This *could* be a logic error on human");
		}else if(i==0){
			throw "Is zero positive?";
		}

	// Note: We usually catch as 'const' to avoid mutation.
	//       Usually pass by reference.
	}catch(const std::logic_error& e){
		std::println("(logic_error) error handling code here: {}", e.what());
	}
	catch(const std::exception& e){
		std::println("(exception) Someting else: {} ",e.what());
	}catch(...){
		std::println("(catch ...) Something I did not think of happened...");
	}

	return 0;
}


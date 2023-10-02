// functor.cpp
#include <iostream>

struct Functor{
public:
	// No paramaters, but we overload ()
	// operator in order to call on object
	int operator()(){
		calls++;
		return calls;
	}

public:
	int calls{0};
};

int main(){

	Functor stateful_variable;

	stateful_variable();
	stateful_variable();
	stateful_variable();

	std::cout << "Call to functor:" 
						<< stateful_variable.calls << std::endl;

	return 0;
}

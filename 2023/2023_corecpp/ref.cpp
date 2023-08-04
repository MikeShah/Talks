// g++ -g -Wall -std=c++20 ref.cpp -o prog

int global;

void PassByPointer(const int* p)
{ 
	global += *p; 
} 
void PassByReference(const int& p) {
	global += p;
}

// Entry point to program
int main(int argc, char* argv[]){

	int value=1;
	
	PassByPointer(&value);
	PassByReference(value);

//	PassByPointer(1); // error!
	PassByReference(1);
	
    return 0;
}


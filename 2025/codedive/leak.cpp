// @file: leak.cpp
// g++ -g leak.cpp -o prog

int main(){

	int* leak = new int[47];
	return 0;
}

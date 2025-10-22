// @file: buf.cpp
#include <vector>
#include <array>
#include <print>

int main(){

	std::array<int,7> buffer;

	buffer[8] = 8;
	std::println("This may print stack memory without foritying source");
	std::println("{}",buffer[7]); 


	return 0;
}

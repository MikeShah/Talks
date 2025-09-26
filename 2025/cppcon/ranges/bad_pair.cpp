// @file: bad_pair.cpp
// Build and run
// g++ -std=c++23 bad_pair.cpp -o prog && ./prog
#include <iostream>
#include <vector>
#include <print>

std::vector<int> DownloadData() { 
	std::vector<int> result{1,3,5,7};
	return result;
}

int main(int argc, char* argv[]){


	auto results = std::all_of(DownloadData().begin(),DownloadData().end(),
							   [](int i) { return i > 2;});

	std::println("{}",results);

	return 0;
}

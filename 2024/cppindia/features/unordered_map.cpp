// @file unordered_map.cpp
// Compile and run: g++ -std=c++23 unordered_map.cpp -o prog && ./prog
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <print>

int main(){
	std::unordered_map<int,std::string> database;
	database.insert({123,"Mike"});
	database.insert({124,"Ankur"});

	if(database.contains(123)){
		std::cout << "User 123 exists...continuing\n";
	}

	// Insert if not existing, or otherwise update
    database[125] = "CppIndia"; 

    // Structured binding to extract keys and values
    for(auto const& [key,value] : database){
        std::cout << key << " | " << value << std::endl; 
    }

    // Statistics of our unordered_map's hashtable
    std::println("bucket_count = {} and load_factor={}",
				database.bucket_count(),database.load_factor());
	
}


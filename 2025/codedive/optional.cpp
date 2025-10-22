// @file: optional.cpp
#include <print>
#include <optional>
#include <string>
#define ERROR_CODE -1000000

bool isValidInput(std::string){
	return true;
}

// Bad version
int ParseIntBad(std::string s){
	bool b = isValidInput(s);
	if(b){
		return std::stoi(s);
	}else{
		return ERROR_CODE; // Which also may happen to be the integer we parsed
	} 
}

// Attempt to parse integer from string
std::optional<int> ParseInt(std::string s){
	std::optional<int> result;
	bool b = isValidInput(s);
	if(b){
		return std::stoi(s);
	}else{
		return std::nullopt;
	} 
}

int main(){
	// Can lead to bad or duplicated code
	if(ParseIntBad("123") != ERROR_CODE){ // Validate input
		std::println("{} ",ParseIntBad("123"));
	}

	// Optional can simplify our code a bit
	auto result = ParseInt("456");
	if(result.has_value()){
		std::println("{}",result.value());
	}

	// Optional can simplify our code a bit, or still allow us to use
	// error codes if we like
	auto result2 = ParseInt("789").value_or(ERROR_CODE);
	std::println("{}",result2);

	return 0;
}

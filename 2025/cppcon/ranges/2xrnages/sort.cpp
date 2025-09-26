#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <print>

int main(){
	// ======================================
	// Prior to Ranges 
	std::vector v1{3,9,7,5,1};
	std::sort(std::begin(v1), std::end(v1));
	std::println("{}",v1);

	// With ranges
	std::vector v2{3,9,7,5,1};
	std::ranges::sort(v2);
	std::println("{}",v2);
	// ======================================


	// ================ We still use iterators with ranges ==========
	// Iterators don't go completely away, we still use them, and we build
	// ranges on top of iterators.
	std::vector data{3,9,7,5,1};
	auto iter = std::ranges::find_if(data, [](int i){ return i==1; }); 	
	if( iter != std::ranges::end(data)){
		std::cout << "I found 1!!!" << *iter << std::endl;
	}

	std::string dna = "GCTCATC";
	auto dna_iter=std::ranges::find(dna,'T');
	if( dna_iter != std::ranges::end(dna)){
		std::cout << "I found T!!!" << *dna_iter << std::endl;
	}


	// ================ std::ranges::begin and end ==========
	std::vector old{1,2,4,8,12,14};
	for(auto start = std::ranges::begin(old);
			 start != std::ranges::end(old);
			 start++){
		std::print("{} ",*start);
	}
	std::println();


	// ======================================
	// Views are a big part of ranges otherwise
	// These are 'lazy ranges' that are cheap to copy, you can
	// think of like std::string_views, std::span, etc.
	// Here's an example:
	std::vector bigCollection = {1,2,3,4,5,6,7,8,9,10};
	// Create a filter
	auto BiggerThanFive = std::views::filter([](int i){return i > 5;});

	// views are applied to ranges 'lazily' each time we evaluate
	// the loop
	// TODO: Should do a GDB walkthrough here.
	// Pipe operator is otherwise new.
	for(auto& elem : bigCollection | BiggerThanFive){
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	// ======================================

	// ======================================
	// We can otherwise use the 'filter_view' that's built in
	// TODO: Need to see filter vs filter_view
	// NOTE: One of the warnings with 'filter_view' is that it 'caches' a value.
	std::vector v3{2,4,6,8,10,12};
	// Nothing happens here
	std::ranges::filter_view myFilter{v3, [](int i){ return i > 5; }};
	for(auto& elem : myFilter){
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	// ======================================


	
	// ======================================
	// Range Adaptors -- to transform ranges to views
	std::vector v4{1,1,1,1,5,6,7,8,9,10,11};
	auto greaterThanFive = v4 | std::views::filter([](int i){return i > 5;});
	for(auto& elem : greaterThanFive){
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	// ======================================


	// ======================================
	// Composition example
	std::vector<std::string> strings = {"Mike","Bob","Miguel","Marissa","Mary"};
	auto startsWithM = [](std::string s){ return s[0] == 'M'; };
	auto longerThan4 = [](std::string s){ return s.length() > 4; };

	// Little exercise here 
	// How many pieces of data do we operate on here?
	for(auto& elem : strings 
					| std::views::filter(startsWithM)
					| std::views::filter(longerThan4)
	){
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	// ======================================


	// ======================================
	// ranges::to
	std::vector<std::string> strings2 = {"mike","bob","miguel","marissa","mary"};
	auto startsWithm = [](std::string s){ return s[0] == 'm'; };
	auto longerThan3 = [](std::string s){ return s.length() > 3; };

	// Little exercise here 
	// How many pieces of data do we operate on here?
	std::vector<std::string> collect =  strings2
							| std::views::filter(startsWithm)
							| std::views::filter(longerThan3)
							| std::ranges::to<std::vector>();	
	std::println("collected: {}",collect);
	// ======================================
	

	// ======================================
	// Another Composition example with Transform
	std::vector v5{1,3,5,7,11,13,17,19};
	auto doubleValue = [](int i){ return i*2; };
	auto AddOne = [](int i){ return i+1; };

	// Notice this time no 'auto&' -- need the 'l-value'
	for(auto elem : v5
					| std::views::transform(doubleValue)
					| std::views::transform(AddOne)
				
	){
		std::cout << elem << " ";
	}
	std::cout << std::endl;
	// ======================================

	// ======================================
	// Here's an example of otherwise using a 'view' to
	// sort of filter our computation.
	std::vector<std::string> winners = {"Mike","Bob","Miguel","Marissa","Mary"};
	
	auto removeMike = [](std::string s){ return s == "Mike";}; 
	auto printSpace= [](std::string s){ std::cout << s << " "; };
	auto startingPoint = std::ranges::views::drop_while(winners, removeMike);

	std::ranges::for_each(startingPoint, printSpace);

	// ======================================


}

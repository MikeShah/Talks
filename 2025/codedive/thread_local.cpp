// @file: thread_local.cpp
#include <iostream>
//#include <print>
#include <mutex>
#include <string>
#include <thread>
 
int 			 global_counter={0};
thread_local int local_counter={0};
std::mutex global_lock;
 
void increment(std::string worker){
	local_counter++;
	{
    	std::lock_guard<std::mutex> lock(global_lock);
		global_counter++;	
	}
	std::cout << worker << " local_counter[" << local_counter 
			  << "] global_counter[" 		<< global_counter 
			  << "]" << std::endl; 
}
 
int main(){
	for(int i=0; i < 20; i++){
	    std::jthread a(increment, "worker1");
		std::jthread b(increment, "worker2");
	}
	return 0; 
}

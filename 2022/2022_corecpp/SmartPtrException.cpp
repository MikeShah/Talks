// SmartPtrException.cpp 
#include <iostream>
class SmartPtr{
    public:
    SmartPtr(){
        data = new int;
    }

    ~SmartPtr(){
		std::cout << "I was called!" << std::endl;
        delete data;
    }
    private:
    int* data;
};


int main(){

    try{
        SmartPtr s;
		throw "some error";
    }catch(...){
		std::cout << "error handling" << std::endl;
		exit(1);	
	}
	std::cout << "Should not reach here" << std::endl;

    return 0;
}



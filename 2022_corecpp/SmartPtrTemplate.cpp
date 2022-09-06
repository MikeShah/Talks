// SmartPtrTemplate.cpp 
#include <iostream>
template <typename T>
class SmartPtr{
    public:
    SmartPtr(){
        data = new T;
    }

    ~SmartPtr(){
        delete data;
    }
    private:
    T* data;
};


int main(){

   	{
        SmartPtr<int> s;
	}    

    return 0;
}



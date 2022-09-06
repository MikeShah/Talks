// SmartPtrSize.cpp 
#include <iostream>
template <typename T>
class SmartPtr{
    public:
    SmartPtr() : m_data(new T), m_size(1){}
	// Handle allocations greater than 1
    SmartPtr(size_t size) : m_data(new T[size]),m_size(size){}

    ~SmartPtr(){
		if(m_data!=nullptr){
			if(m_size>1){
				delete[] m_data;
			}else{
				delete m_data;
			}
		}
    }
    private:
    T* m_data;
	size_t m_size;
};

int main(){
   	{
        SmartPtr<int> s;
        SmartPtr<int> s2(50);
	}    
    return 0;
}



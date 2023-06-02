// SmartPtrUnique.cpp 
#include <iostream>
template <typename T>
class SmartPtr{
    public:
    SmartPtr() : m_data(new T), m_size(1){}
	// Handle allocations greater than 1
    SmartPtr(size_t size) : m_data(new T[size]),m_size(size){}

    ~SmartPtr(){
		destroy();
    }
	// Illegal Operators
	// Assignment operator
	SmartPtr<T>& operator=(const SmartPtr<T>& rhs) = delete;
	SmartPtr<T>(const SmartPtr<T>& rhs) = delete;

	// Allow move constructor 
	SmartPtr<T>(const SmartPtr<T>&& rhs){
		// ...	
	}
	// Allow move operator Assignment
	SmartPtr<T>& operator=(const SmartPtr<T>&& rhs) noexcept{
		// ...
		return *this;	
	}

    private:
    
	void destroy(){
		if(m_data!=nullptr){
			if(m_size>1){
				delete[] m_data;
			}else{
				delete m_data;
			}
			m_size=0;
		}
	}
	
	T* m_data;
	size_t m_size;
};

// SmartPtrUnique.cpp 
int main(){
   	{
        SmartPtr<int> s;
        SmartPtr<int> s1;
        SmartPtr<int> s2;

		// Only 1 owner at the end of this
		// No more double-free issue
		s = std::move(s2);
		s1 = std::move(s2);
	}    
    return 0;
}



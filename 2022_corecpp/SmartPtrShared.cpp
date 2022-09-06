// SmartPtrShared.cpp 
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
// SmartPtrShared.cpp 
	SmartPtr<T>& operator=(const SmartPtr<T>& rhs){		
		if(this==&rhs){
			return *this;
		}
		// destroy memory
		destroy();	
		// Assign pointee to rhs
		m_data = rhs.m_data;		m_size = rhs.m_size;

		// Do some book keeping!
		rhs.m_refcount++;
		m_refcount = rhs.m_refcount;

		return *this;
	}	

    private:
	void destroy(){
		if(m_data!=nullptr && m_refcount ==0){
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
	size_t m_refcount;
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



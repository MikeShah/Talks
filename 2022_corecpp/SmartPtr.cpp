// SmartPtr.cpp 
class SmartPtr{
    public:
    SmartPtr(){
        data = new int;
    }

    ~SmartPtr(){
        delete data;
    }
    private:
    int* data;
};


int main(){

    {
        SmartPtr s;
    }

    return 0;
}

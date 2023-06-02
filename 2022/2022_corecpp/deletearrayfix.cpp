// deletearrayfix.cpp
void RunMainLoop(){
    
    while(true){
        int* allocateResource = new int[500];
        /// ...
        delete[] allocateResource;
    }   
}

int main(){
    RunMainLoop();   
    return 0;
}



// memoryleakfix.cpp
void RunMainLoop(){
    
    while(true){
        int* allocateResource = new int;
        /// ...
        delete allocateResource;
    }   
}

int main(){
    RunMainLoop();   
    return 0;
}



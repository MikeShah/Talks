// memoryleak.cpp
void RunMainLoop(){
    
    while(true){
        int* allocateResource = new int;
        /// ...
    }   
}

int main(){
    RunMainLoop();   
    return 0;
}



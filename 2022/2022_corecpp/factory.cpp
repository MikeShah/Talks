// factory.cpp
object* MakeAndAllocateNewObject(){
    // ...
}

// deletearray.cpp
void RunMainLoop(){
    
    std::vector<object*> objects;
    while(true){
        object* o = MakeAndAllocateNewObject();
        objects.push_back(o);
    }
    // Do I delete everything in vector here?
    /// ...
}

int main(){
    RunMainLoop();   
    return 0;
}



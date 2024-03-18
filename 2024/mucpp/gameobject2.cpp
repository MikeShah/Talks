// gameobject.cpp
struct GameObject{
    
    std::string name;
    Mesh        m;  // 3D data
    Texture     t;  // texture 
    Position    p;  // Position
    Transform   t;  // rotation
    
    Behavior    b;  // Function ptr
                    // to some action
    
    GameObject(){ }
    ~GameObject() { }

};

int main(){

    // Stack may be too small or valuable
    // to allocate our objects on
    // GameObject[500] objects;

    // Allocate on the heap?
    GameObject* objects = new GameObject[500];

    return 0;
}

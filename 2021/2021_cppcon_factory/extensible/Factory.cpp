#include "Factory.hpp"
#include "GameObjects.hpp"

// Initialize our static
MyGameObjectFactory::CallBackMap MyGameObjectFactory::s_Objects;

void MyGameObjectFactory::RegisterObject(const std::string& type, CreateObjectCallback cb){
    s_Objects[type] = cb;
}
// Unregister a user created object type
// Remove from our map
void MyGameObjectFactory::UnregisterObject(const std::string& type){
    s_Objects.erase(type);
}
// Our Previous 'Factory Method'
//
IGameObject* MyGameObjectFactory::CreateSingleObject(const std::string& type){
    CallBackMap::iterator it = s_Objects.find(type);
    if(it!=s_Objects.end()){
        // Call the callback function
        return (it->second)();
    }
    return nullptr;
}




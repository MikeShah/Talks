#include <vector>
#include <memory>

#include "Factory.hpp"
#include "GameObjects.hpp"


int main(){
    // Formerly our units1 and units2
    std::vector<std::shared_ptr<IGameObject>> gameObjectCollection; 
    // Add the correct object to our collection
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE_IN_AIR));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::BOAT));
    gameObjectCollection.push_back(CreateObjectFactory(ObjectType::BOAT));

    // Main Game Loop
    while(true){
        // Iterate through your game object
        // update them, run logic, etc.
        for(auto& e: gameObjectCollection){
            e->Update();
            e->Render();
        } 
    }

    return 0;
}

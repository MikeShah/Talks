// @directory data-driven
// g++ -std=c++17 main.cpp Factory.cpp -I./
#include <vector>
#include <memory>
#include <fstream>
#include <string>

#include "Factory.hpp"
#include "GameObjects.hpp"

int main(){
    std::vector<std::shared_ptr<IGameObject>> gameObjectCollection; 
    // Add the correct object to our collection
    // based on a .txt file
    std::string line;
    std::ifstream myFile("level1.txt");
    if(myFile.is_open()){
        while(std::getline(myFile,line)){
            if(line=="plane"){
                gameObjectCollection.push_back(CreateObjectFactory(ObjectType::PLANE));
            }
            /* You get the idea...
            else if(line==""){
            
            }
            */
        }
    }

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

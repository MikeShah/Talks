// factory.cpp
#include <map>
#include <string>
#include <algorithm>

struct ExtrinsicState{
    // Extrinsic State
    Params params;
    Position p;
};

// 'Model' is the flyweight
struct Model{
    // Inrinsic State
//    const Mesh m;
//    const Bark b;
//    const Leaves l;

    // Extrinisc state is passed into
    // the flyweight to do the 'unique'
    // thing.
    void DrawOperation(ExtrinsicState e){
        // Draw mesh at some 'position p'
        // from the extrinisic state, but
        // the geometry itself (the mesh)
        // does not otherwise change.
    }

};

// a.k.a. 'Resource Manager'
struct FlyWeightModelFactory{
    
    Model* GetFlyweight(std::string key){
        std::map<std::string,Model*>::iterator itr;

        if( (itr=mFlyWeightMap.find(key)) != mFlyWeightMap.end()){
            return itr->second;
        }else{
           Model* m = new Model;
           mFlyWeightMap[key]=m;
           return m;
        }
    }

    // Map or another data structure to 'lookup' an exising flyweigt
    std::map<std::string,Model*> mFlyWeightMap;
};



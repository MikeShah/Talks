// model_extrinsic.cpp

struct ExtrinsicState{
    // Extrinsic State
    Params params;
    Position p;
};

// 'Model' is the flyweight
struct Model{
    // Inrinsic State
    const Mesh m;
    const Bark b;
    const Leaves l;

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





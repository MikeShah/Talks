module ray;

import vec3;

struct Ray{
    /// Constructor
    // TODO: pass in origin and direction by reference
    this(Vec3 origin, Vec3 direction){
        m_origin    = origin;
        m_direction = direction;
    }

    /// Retrieve the ray as parameterized by value 't'
    Vec3 At(float t) {
        return m_origin + (t*m_direction);
    }

    /// Return the origin from which the ray is cast
    // TODO: Return const?
    Vec3 GetOrigin() {
        return m_origin;
    }

    /// Returns the direction of a Ray
    // TODO: Return const?
    Vec3 GetDirection() {
        return m_direction;
    }

    /// Override toString for convenient printing 
    string toString(){
        import std.stdio;
        import std.conv;
        return "origin: "~m_origin.toString()~" direction: "~m_direction.toString();  
    }    

    // Private member variables
    private Vec3 m_origin;
    private Vec3 m_direction;
}

unittest{
    Ray r =  Ray(Vec3(0.0,0.0,0.0), Vec3(0.0,0.0,1.0));

    Vec3 expectedResult = Vec3(0.0,0.0,0.5);
   // assert(r.At(0.5) == expectedResult);
}

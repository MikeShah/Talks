/***********************************
 * Brief summary of what
 * myfunc does, forming the summary section.
 *
 * First paragraph of synopsis description.
 *
 * Second paragraph of
 * synopsis description.
 */
module vec3;

class Vec3{
    import std.meta;
    import std.math;

    /// Constructor for a Vec3
    this(){
        e[0] = 0.0;
        e[1] = 0.0;
        e[2] = 0.0;
    }
    /// Constructor initializing the elements
    this(double e0, double e1, double e2){
        e[0] = e0;
        e[1] = e1;
        e[2] = e2; 
    }
    /// Construtor from a vector
    this(const Vec3 v){
        e[0] = v.e[0];
        e[1] = v.e[1];
        e[2] = v.e[2];
    }
    
    /// Returns the length of the vector
    double Length() const{
        if(IsZero()){
            return 0;
        }

        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);        
    }

    /// Alias of 'Length' function for Magnitude
    alias Magnitude = Length;

    /// Returns the length of a vector squared,
	/// thus avoiding a sqrt operation
    double LengthSquared() const{
        if(IsZero()){
            return 0;
        }

        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];        
    }

    /// Normalize a vector into a unit vector
    void Normalize() {
        if( !IsZero()){
            double length = Length();
            e[0] /= length;
            e[1] /= length;
            e[2] /= length;
        }
    }

    /// Alias of 'Normalize' for British Spelling
    alias Normalise() = Normalize();

    double X() const { return e[0]; }
    double Y() const { return e[1]; }
    double Z() const { return e[2]; }

    /// Test if this is a zero vector
    bool IsZero() const{
        return (abs(e[0]) <= 0.000001 &&
                abs(e[1]) <= 0.000001 && 
                abs(e[2]) <= 0.000001);
    }

    /// Retrieve a unit vector
    Vec3 ToUnitVector(){
        // Compute the length once
        auto len = Length();
        // TODO: Throw exceptoin if lenth is 0
        if(len!=0){
            e[0] = e[0] / len;
            e[1] = e[1] / len;
            e[2] = e[2] / len;
        }
        return this;
    }

    /// Return true or false if this is a unit vector
    bool IsUnitVector() const{
        if( abs(sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]) -1.0) < 0.000001){
            return true;
        }
        return false;        

    }

    /// Prints out the vector to stdout
    override string toString(){
        import std.stdio;
        import std.conv;
        return to!string(X())~","~to!string(Y())~","~to!string(Z()); 
    }

    /// Unary operators
    Vec3 opUnary(string s)() if (s == "-"){
        e[0] = -e[0];
        e[1] = -e[1];
        e[2] = -e[2]; 
        return this;
    }

    /// Return an individual index
    // TODO: See if I can bounds check i or use
    //       a contract
    ref double opIndex(uint i) { 
        return e[i]; 
    }


    /// Test for opreator equality
     bool opEquals(const Vec3 rhs) {
        if (abs (e[0]- rhs.e[0]) < 0.000001 &&
            abs (e[1]- rhs.e[1]) < 0.000001 &&
            abs (e[2]- rhs.e[2]) < 0.000001)
        {
            return true;
        }else{
            return false;
        }
    } 


    /// Binary Operations with a Vector
    // TODO: Add operations for +=, -=, /=, *=, etc.
    auto opBinary(string op)(const Vec3 rhs){
        Vec3 result = new Vec3(0.0,0.0,0.0);
        if(op=="*"){ 
           result[0] = e[0] * rhs.e[0];
           result[1] = e[1] * rhs.e[1];
           result[2] = e[2] * rhs.e[2];
        }
        else if(op=="/"){ 
           result[0] = e[0] / rhs.e[0];
           result[1] = e[1] / rhs.e[1];
           result[2] = e[2] / rhs.e[2];
        }
        else if(op=="+"){ 
           result[0] = e[0] + rhs.e[0];
           result[1] = e[1] + rhs.e[1];
           result[2] = e[2] + rhs.e[2];
        }
        else if(op=="-"){ 
           result[0] = e[0] - rhs.e[0];
           result[1] = e[1] - rhs.e[1];
           result[2] = e[2] - rhs.e[2];
        }
        return result;
    }


    /// Handle multiplication and division of a scalar
    /// for a vector
    Vec3 opBinary(string op)(double rhs){
        Vec3 result = new Vec3(0.0,0.0,0.0);
        if(op=="*"){ 
           result[0] = e[0] * rhs;
           result[1] = e[1] * rhs;
           result[2] = e[2] * rhs;
        }
        else if(op=="/"){ 
           result[0] = e[0] / rhs;
           result[1] = e[1] / rhs;
           result[2] = e[2] / rhs;
        }
        else if(op=="+"){ 
           result[0] = e[0] + rhs;
           result[1] = e[1] + rhs;
           result[2] = e[2] + rhs;
        }
        else if(op=="-"){ 
           result[0] = e[0] - rhs;
           result[1] = e[1] - rhs;
           result[2] = e[2] - rhs;
        }
        return result;
    }

    /// Handle multiplication and division of
    /// scalar and a Vec3.
    // TODO: Explain why we need opBinaryRight and
    //       opBinary operations
    Vec3 opBinaryRight(string op)(double rhs){
        Vec3 result = new Vec3(0.0,0.0,0.0);
        if(op=="*"){ 
           result[0] = e[0] * rhs;
           result[1] = e[1] * rhs;
           result[2] = e[2] * rhs;
        }
        else if(op=="/"){ 
           result[0] = e[0] / rhs;
           result[1] = e[1] / rhs;
           result[2] = e[2] / rhs;
        }
        else if(op=="+"){ 
           result[0] = e[0] + rhs;
           result[1] = e[1] + rhs;
           result[2] = e[2] + rhs;
        }
        else if(op=="-"){ 
           result[0] = e[0] - rhs;
           result[1] = e[1] - rhs;
           result[2] = e[2] - rhs;
        }
        return result;
    }


    // Store x,y,z components.
    private double[3] e;
}


/// Compute the dot product of two vectors
double DotProduct(const Vec3 v1, const Vec3 v2){
    if(v1.IsZero() && v2.IsZero()){
        return 0;
    }

    return v1.X()*v2.X() + v1.Y()*v2.Y() + v1.Z()*v2.Z();
}

/// Compute the Cross product the vector
Vec3 CrossProduct(const Vec3 v1, const Vec3 v2){
    float x = v1.Y()*v2.Z() - v1.Z()*v2.Y();
    float y = v1.Z()*v2.X() - v1.X()*v2.Z();
    float z = v1.X()*v2.Y() - v1.Y()*v2.X();

    return new Vec3(x,y,z);
}



/// Vec3 default constructor initialized to zero
unittest {
    Vec3 v = new Vec3();
    assert(v[0] == 0);
    assert(v[1] == 0);
    assert(v[2] == 0);
}

/// Vec3 constructor with parameteres
unittest {
    Vec3 v = new Vec3(1,2,3);
    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
}


/// Vec3 negation 
unittest {
    Vec3 v = new Vec3(1,2,3);
    v = -v;
    assert(v[0] == -1);
    assert(v[1] == -2);
    assert(v[2] == -3);
}

/// Vec3 length and magnitude tests
unittest{
    Vec3 v = new Vec3;
    assert(v.Length() ==0);
}

/// Check magnitude of Vec3 is 1 after normalizing the vector
unittest{
    Vec3 v = new Vec3(4,5,6);
    v.Normalize();

    assert( (1.0 - v.Length()) <= 0.000001);
}

/// Test if a vector is a zero vector
unittest{
    Vec3 v1 = new Vec3;
    Vec3 v2 = new Vec3(1,2,3);

    assert(true == v1.IsZero());
    assert(false == v2.IsZero());
}

/// Compute the dot products of two zero vectors 
unittest{
    Vec3 v1 = new Vec3;
    Vec3 v2 = new Vec3;

    v1.Normalize();
    v2.Normalize();

    assert( DotProduct(v1,v2) <= 0.000001);
}
/// Compute the dot products of two normalized vectors 
unittest{
    Vec3 v1 = new Vec3(1,2,3);
    Vec3 v2 = new Vec3(1,2,3);

    v1.Normalize();
    v2.Normalize();

    assert( DotProduct(v1,v2) == 1);
}

/// Cross product test
unittest{
    Vec3 v1 = new Vec3(2,3,4);
    Vec3 v2 = new Vec3(5,6,7);

    Vec3 result = CrossProduct(v1,v2);
    
    assert(result.X() == -3);
    assert(result.Y() == 6);
    assert(result.Z() == -3);
}

/// Binary Operations Test for Addition
// TODO: Need to do other operations. 
unittest{
    Vec3 v1 = new Vec3(2,3,4);
    Vec3 v2 = new Vec3(5,6,7);

    Vec3 result = v1 + v2;
    
    assert(result.X() == 7);
    assert(result.Y() == 9);
    assert(result.Z() == 11);
}

/// Unit vector tests
unittest{
    Vec3 v1 = new Vec3(2,3,4);
    Vec3 v2 = new Vec3(1,0,0);

    assert(v1.IsUnitVector() == false);
    assert(v2.IsUnitVector() == true);
    assert(v1.ToUnitVector().IsUnitVector() == true);

    Vec3 v3 = new Vec3(0.5,0.25,0.115);
    assert(v3.ToUnitVector().IsUnitVector() == true);

    Vec3 v4 = new Vec3(0.0,0.0,0.0);
    assert(v4.ToUnitVector().IsUnitVector() == false);

    Vec3 v5 = new Vec3(1.96,2.98,3.1);
    assert(v5.ToUnitVector().IsUnitVector() == true);

    Vec3 v6 = new Vec3(-0.98,0.97,0.0);
    assert(v6.ToUnitVector().IsUnitVector() == true);
}

/// Scalar multiply by vector
unittest{
    Vec3 v1 = new Vec3(2,4,6);
    Vec3 result = 0.5 * v1;
    assert(result.X() == 1);
    assert(result.Y() == 2);
    assert(result.Z() == 3);
}

/// Scalar division of a vector
unittest{
    Vec3 v1 = new Vec3(2,4,6);
    Vec3 result = v1/2;
    assert(result.X() == 1);
    assert(result.Y() == 2);
    assert(result.Z() == 3);
}

/// Addition of vector and Scalar division of a vector
unittest{
    Vec3 v1 = new Vec3(2,4,6);
    Vec3 result = (new Vec3(1,2,3)) + v1/2;

    assert(result.X() == 2);
    assert(result.Y() == 4);
    assert(result.Z() == 6);
}

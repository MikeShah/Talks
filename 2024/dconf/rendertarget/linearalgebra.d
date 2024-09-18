import std.math;

struct vec2(T){
	union{
		T[2] data;
		struct{
			T x,y;
		}
	}
	this(T x, T y){
		this.x = x;
		this.y = y;
	}
	vec2!T opBinary(string op)(const vec2!T rhs){
		auto result = vec2!T(x.init,y.init);
		mixin("result.x = this.x "~op~" rhs.x;");
		mixin("result.y = this.y "~op~" rhs.y;");
		return result;
	}
	void opOpAssign(string op)(const vec2!T rhs){
		mixin("this.x "~op~"= rhs.x;");
		mixin("this.y "~op~"= rhs.y;");
	}
	void opAssign(const vec2!T rhs){
		x = rhs.x;
		y = rhs.y;
	}
}

struct vec3(T){
	union{
		T[3] data;
		struct{
			T x,y,z;
		}
	}

	this(T)(T x, T y, T z){
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	T magnitude() const{
		// TODO: cache this value, or add a 'dirty' bit perhaps
		return sqrt(x*x + y*y + z*z);	
	}
	
	vec3!T opUnary(string op)()
		if(op=="-")
	{
		// TODO: Maybe remove .init, since we don't need to do work here.
		vec3!T result = vec3!T(x.init, y.init, z.init);
		mixin("result.x = "~op~"result.x;");
		mixin("result.y = "~op~"result.y;");
		mixin("result.z = "~op~"result.z;");
		return result;	
	}

	vec3!T opBinary(string op)(vec3!T rhs){
		vec3!T result = vec3!T(x.init, y.init, z.init);
		mixin("result.x = this.x"~op~"rhs.x;");
		mixin("result.y = this.y"~op~"rhs.y;");
		mixin("result.z = this.z"~op~"rhs.z;");
		return result;
	}

//	vec3!T opBinary(string op)(vec3!T rhs) {
//        return vec3!float(this.x + rhs.x, this.y + rhs.y, this.z + rhs.z);
//  }
	
	void opOpAssign(string op)(vec3!T rhs){
		mixin("this.x "~op~"= rhs.x;");
		mixin("this.y "~op~"= rhs.y;");
		mixin("this.z "~op~"= rhs.z;");
	}
	void opAssign(vec3!T rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
	}

}

struct mat3(T){
	T[3][3] data;

	vec3!T opIndex()(size_t row){
		return vec3!T(data[row][0],data[row][1],data[row][2]);
	}
}

struct mat4(T){
	T[4][4] data;

	this(T)(T[16] floats){
		// TODO: This could be wrong -- need to check if it is column order
		data[0][0] = floats[0];
		data[0][1] = floats[1];
		data[0][2] = floats[2];
		data[0][3] = floats[3];
		data[1][0] = floats[4];
		data[1][1] = floats[5];
		data[1][2] = floats[6];
		data[1][3] = floats[7];
		data[2][0] = floats[8];
		data[2][1] = floats[9];
		data[2][2] = floats[10];
		data[2][3] = floats[11];
		data[3][0] = floats[12];
		data[3][1] = floats[13];
		data[3][2] = floats[14];
		data[3][3] = floats[15];
	}

	void opUnary(string op)(){
		foreach(ref e;data){
			mixin("e = "~op~"e;");
		}
	}

	mat4!T opBinary(T)(mat4!T rhs){
		mat4!T result;
		return result;
	}
	
}

	vec3!T normalize(T)(vec3!T v){
		vec3!T r;
		auto denominator = v.magnitude();	
		r.x = v.x/denominator;
		r.y = v.y/denominator;
		r.z = v.z/denominator;
		return r;
	}

	// TODO:
	vec3!T cross(T)(vec3!T a, vec3!T b){
		return vec3!T(0,0,0);
	}

mat4!T lookAt(T)(vec3!T eye, vec3!T target, vec3!T up){
    vec3!T forward = (target - eye).normalize();
    vec3!T right = normalize(cross(up, forward));
    vec3!T newUp = cross(forward, right);

    mat4!T matrix = mat4!T([
        right.x, right.y, right.z, 0,
        newUp.x, newUp.y, newUp.z, 0,
        -forward.x, -forward.y, -forward.z, 0,
        0, 0, 0, 1]) ;

		auto negateEye = -eye;
		mat4!float translation = translationMatrix!T(negateEye);
    mat4!float  result = matrix * translation;
		return result;
}

mat4!T translationMatrix(T)(vec3!T translation) {
	auto result = mat4!T([
        1, 0, 0, translation.x,
        0, 1, 0, translation.y,
        0, 0, 1, translation.z,
        0, 0, 0, 1
    ]);

    return result;
 }

vec3!T rotate(T)(mat3!T matrix, vec3!T vector){
	vec3!T result;
	return result;
}

// Rotate a vector about an angle
vec3!T rotate(T)(T angle, vec3!T vec){
	vec3!T result;
	return result;
}

mat3!float OuterProduct(T)(vec3!T a, vec3!T b){
	// Compute the outer product
    float[3][3] outerProduct;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outerProduct[i][j] = a.data[i] * b.data[j];
        }
    }
	mat3!float result;
	result.data= outerProduct;
	return result;
}

// Make vec4 from a vec3
vec4!T makeVec4(T)(vec3!T v){
	return vec4!(v.x,v.y,v.z,0.f);
} 



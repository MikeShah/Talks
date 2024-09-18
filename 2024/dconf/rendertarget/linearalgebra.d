// SEARCH FOR T:ODO: 
import std.math;

struct vec2(T){

		invariant{
				assert(data[0] != float.init);
				assert(data[1] != float.init);
		}
		@disable this();

		union{
				struct{
						T[2] data;
				}
				struct{
						T x,y;
				}
		}

		this(T)(T value){
				T.x = value;
				T.y = value;
		}

		this(T)(T x, T y){
				this.x = x;
				this.y = y;
		}
		vec2!T opUnary(string op)()
				if(op=="-")
				{
						return vec2!T(-x,-y);	
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
		void opAssign(T)(const vec2!T rhs){
				x = rhs.x;
				y = rhs.y;
		}
}

struct vec3(T){
		@disable this();

		union{
				struct{
						T[3] data;
				}
				struct{
						T x,y,z;
				}
		}

		this(T value){
				this.x = value;
				this.y = value;
				this.z = value;
		}

		this(T x, T y, T z){
				this.x = x;
				this.y = y;
				this.z = z;
		}

		this(vec3!T v){
				this.x = v.x;
				this.y = v.y;
				this.z = v.z;
		}

		T magnitude() const{
				// TODO: cache this value, or add a 'dirty' bit perhaps
				// TODO: Cast to float or perhaps integer for integer types
				if(is(typeof(T) == float)){
						return sqrt((x*x + y*y + z*z));
				}else {
						import std.stdio;
						return cast(T)1;
				}
		}

		vec3!T opUnary(string op)()
				if(op=="-")
				{
						return vec3!T(-x,-y,-z);	
				}

		vec3!T opBinary(string op)(vec3!T rhs){
				vec3!T result = vec3!T(T.init);
				mixin("result.x = this.x"~op~"rhs.x;");
				mixin("result.y = this.y"~op~"rhs.y;");
				mixin("result.z = this.z"~op~"rhs.z;");
				return result;
		}


		void opOpAssign(string op)(vec3!T rhs){
				mixin("this.x "~op~"= rhs.x;");
				mixin("this.y "~op~"= rhs.y;");
				mixin("this.z "~op~"= rhs.z;");
		}
		void opAssign(T)(vec3!T rhs){
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
		}

}

struct mat3(T){
		T[3][3] data;

		void makeIdentity(T)(){
				data[0][0] = cast(T)1;
				data[1][1] = cast(T)1;
				data[2][2] = cast(T)1;
		}

		vec3!T opIndex()(size_t row){
				return vec3!T(data[row][0],data[row][1],data[row][2]);
		}
}

// NOTE: Could be wrong!
vec3!T MatrixTimesVector(T)(mat3!T m, vec3!T vector) {
		return vec3!T(
						m.data[0][0] * vector.x + m.data[0][1] * vector.y + m.data[0][2] * vector.z,
						m.data[1][0] * vector.x + m.data[1][1] * vector.y + m.data[1][2] * vector.z,
						m.data[2][0] * vector.x + m.data[2][1] * vector.y + m.data[2][2] * vector.z
						);
}

struct mat4(T){
		T[4][4] data;

		void makeIdentity(T)(){
				data[0][0] = cast(T)1;
				data[1][1] = cast(T)1;
				data[2][2] = cast(T)1;
				data[3][3] = cast(T)1;
		}
		void makeZero(T)(){
				foreach(ref elem; data){
						elem = cast(T)0;
				}
		}

		T[] flatten(T)(){
				T[] result = new T[16];
				int pos=0;
				foreach(row ; data){
						foreach(col ; row){
								result[pos] =col;
								pos++;
						}
				}
				return result;
		}

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

		mat4!T opBinary(string op)(mat4!T rhs){
				mat4!T result;
				result.makeIdentity!T();				
				import std.stdio;
				writeln("This hould be called after");

				for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
								result.data[i][j] = 0;
								for (int k = 0; k < 4; k++) {
										result.data[i][j] += this.data[i][k] * rhs.data[k][j];
								}
						}
				}

				return result;
		}

}

void normalize(T)(vec3!T v){
		auto denominator = v.magnitude();	
		if(denominator==0.0f){
				return;
		}
		v.x = v.x/denominator;
		v.y = v.y/denominator;
		v.z = v.z/denominator;
}

vec3!T cross(T)(vec3!T a, vec3!T b){
		vec3!T result = vec3!T(T.init);
		import std.stdio;
		writeln("\t",result);
		result.x = a.y*b.z - a.z*b.y;
		result.y = a.z*b.x - a.x*b.z;
		result.z = a.y*b.z - a.y*b.x;
		writeln("\t",result);

		assert(result.x != float.init);
		assert(result.y != float.init);
		assert(result.z != float.init);

		return result;
}

mat4!T lookAt(T)(vec3!T eye, vec3!T target, vec3!T up){
		import std.stdio;

		writeln("==============");
		writeln("lookat");
		vec3!T forward = (target - eye);
		forward.normalize();
		writeln("\t",__FILE__,":",__LINE__,"|forward|",forward);
		vec3!T right = vec3!T(T.init);
		right = cross(up, forward);
		right.normalize();
		writeln("\t",__FILE__,":",__LINE__,"|right|",right);
		vec3!T newUp = cross(forward, right);
		writeln("\t",__FILE__,":",__LINE__,"|newUp|",newUp);

		mat4!T matrix = mat4!T([
						right.x, right.y, right.z, 0,
						newUp.x, newUp.y, newUp.z, 0,
						-forward.x, -forward.y, -forward.z, 0,
						0, 0, 0, 1]) ;
		writeln("lookat matrix:\t",matrix);

		vec3!float negateEye = -eye;
		mat4!float translation = MakeTranslationMatrix!float(negateEye);
		writeln("translation:",__FILE__,":",__LINE__,"|",translation);
		mat4!float result = matrix * translation;

		writeln(__FILE__,":",__LINE__,"|",result);
		writeln("==============");

		return result;
}

mat4!T MakeTranslationMatrix(T)(vec3!T translation) {
		mat4!T result = mat4!T([
						1, 0, 0, translation.x,
						0, 1, 0, translation.y,
						0, 0, 1, translation.z,
						0, 0, 0, 1
		]);

		return result;
}



// Rotate a vector about an angle
mat3!T rotate(T)(T angle, vec3!T vec){

		import std.stdio;

		mat3!T result;
		result.makeIdentity!T();
		auto axis = vec3!T(vec);
		axis.normalize();

		auto SinTheta = sin(angle);
		auto CosTheta = cos(angle);
		auto CosValue = 1.0f - CosTheta;

		result.data[0][0] = (axis.x * axis.x * CosValue) + CosTheta;
		result.data[0][1] = (axis.x * axis.y * CosValue) + (axis.z * SinTheta);
		result.data[0][2] = (axis.x * axis.z * CosValue) - (axis.y * SinTheta);

		result.data[1][0] = (axis.y * axis.x * CosValue) - (axis.z * SinTheta);
		result.data[1][1] = (axis.y * axis.y * CosValue) + CosTheta;
		result.data[1][2] = (axis.y * axis.z * CosValue) + (axis.z * SinTheta);

		result.data[2][0] = (axis.x * axis.x * CosValue) + (axis.y * SinTheta);
		result.data[2][1] = (axis.x * axis.y * CosValue) - (axis.z * SinTheta);
		result.data[2][2] = (axis.x * axis.z * CosValue) + CosTheta;


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
		result.makeIdentity!float();
		result.data= outerProduct;
		return result;
}

// Make vec4 from a vec3
vec4!T makeVec4(T)(vec3!T v){
		return vec4!(v.x,v.y,v.z,0.f);
} 




// vec3 tests
unittest{
		auto v1 = vec3!int(1,2,3);
		auto v2 = vec3!int(4,5,6);
		auto result1 = v1+v2;
		assert(result1.x == 5);
		assert(result1.y == 7);
		assert(result1.z == 9);

		auto result2 = v2-v1;
		assert(result2.x == 3);
		assert(result2.y == 3);
		assert(result2.z == 3);

		vec3!int result3 = -v1;
		assert(result3.x == -1);
		assert(result3.y == -2);
		assert(result3.z == -3);

		vec3!int result4 = vec3!int(5);
		assert(result4.x == 5);
		assert(result4.y == 5);
		assert(result4.z == 5);

		vec3!int result5 = vec3!int(5);
		result4 += result5;
		assert(result4.x == 10);
		assert(result4.y == 10);
		assert(result4.z == 10);


}

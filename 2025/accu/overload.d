import std.typecons;
import std.stdio;

// Templated struct
struct Vector3(T){
	T[3] elements;

	typeof(this) opBinary(string op)(double rhs)
		// template constraint
		if(op=="*" || op=="/")
	{
		auto result = typeof(this)([0.0,0.0,0.0]);
		mixin("result.elements[0] = elements[0]", op, "rhs;");
		mixin("result.elements[1] = elements[1]", op, "rhs;");
		mixin("result.elements[2] = elements[2]", op, "rhs;");
		return result;
	}

}

alias Vec3f = Vector3!float;

void main(){

	Vec3f v = Vec3f([1.0f,1.0f,1.0f]);

	v = v * 2.0f;
//	v = v + 2.0f; // Illegal

	writeln(v);
}

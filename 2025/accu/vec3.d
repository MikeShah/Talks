import std.typecons;
import std.stdio;

// Templated struct
struct Vector3(T){
	T[3] elements;
}

// Easily create alias
alias Vec3i = Vector3!int;
alias Vec3f = Vector3!float;
alias Vec3d = Vector3!double;

// Create alias with more type-safety (i.e. Point3 is not same as Vector3.
alias Point3f = Typedef!(Vec3f);

void main(){

	Vec3f v;
	writeln(v);

	Point3f p;
	writeln(p);

	assert(!is(p == v), "These are not the same types");
}

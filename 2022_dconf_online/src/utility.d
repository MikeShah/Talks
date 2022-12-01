module utility;

import vec3;

import std.random;

// global random number generator
Random rnd;

// Initialize once in the module our random
// number generator.
static this(){
    rnd = Random(unpredictableSeed);
}

/// Generate a random double from 0..1
double GenerateRandomDouble(){
	return uniform01(rnd);
}


/// Generate a random double from a range
double GenerateRandomDouble(double min, double max){
	return min + (max-min)*uniform01(rnd);
}

Vec3 GenerateRandomVec3(){
	return new Vec3(GenerateRandomDouble(),GenerateRandomDouble(),GenerateRandomDouble());
}

Vec3 GenerateRandomVec3(double min, double max){
	return new Vec3(GenerateRandomDouble(min,max),GenerateRandomDouble(min,max),GenerateRandomDouble(min,max));
}

/// Test range of GenerateRandomDouble()
unittest{
	assert(GenerateRandomDouble() < 1.00001);
	assert(GenerateRandomDouble() > -0.000001);
}

/// Test range of GenerateRandomDouble()
unittest{
	assert(GenerateRandomDouble(5,9) > 4.999999);
	assert(GenerateRandomDouble(5,9) < 9.000001);
}

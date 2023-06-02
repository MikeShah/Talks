module utility;

import vec3;

import std.random;

/// Generate a random float from 0..1
Random rnd;

static this() { rnd = Random(unpredictableSeed); }

float GenerateRandomFloat(){
	return uniform01(rnd);
}


/// Generate a random float from a range
float GenerateRandomFloat(float min, float max){
	return min + (max-min)*uniform01(rnd);
}

Vec3 GenerateRandomVec3(){
	return Vec3(GenerateRandomFloat(),GenerateRandomFloat(),GenerateRandomFloat());
}

Vec3 GenerateRandomVec3(float min, float max){
	return Vec3(GenerateRandomFloat(min,max),GenerateRandomFloat(min,max),GenerateRandomFloat(min,max));
}

/// Test range of GenerateRandomFloat()
unittest{
	assert(GenerateRandomFloat() < 1.00001);
	assert(GenerateRandomFloat() > -0.000001);
}

/// Test range of GenerateRandomFloat()
unittest{
	assert(GenerateRandomFloat(5,9) > 4.999999);
	assert(GenerateRandomFloat(5,9) < 9.000001);
}

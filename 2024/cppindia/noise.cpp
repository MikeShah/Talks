#include <iostream>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <functional>

float smoothStepRemap(const float a, const float b, const float t){
	float tRemapSmoothstep = t*t* (3-2*t);
	return std::lerp(a,b,tRemapSmoothstep);
}

float cosineRemap(const float a, const float b, const float t){
	assert(t >=0 && t <=1);
	float tRemapCosine = (1 - std::cos(t* M_PI)) * 0.5f;
	return std::lerp(a,b,tRemapCosine);
}


/*
float smoothNoise(const float a, const float b, const float t){
	assert(t >=0 && t <=1);
	float tRemap = smoothFunc(t);
	return std::lerp(a,b,tRemap);
}
*/

// Value Noise 1D function
// C++ 17 -- use 'auto' here
template<auto InterpolationFunc>
struct ValueNoise1D{
	// Populate Value Noise with random values
	ValueNoise1D(size_t seed = 2024){
		srand(seed);
		for(size_t i=0; i < MAX_VERTICES; ++i){
			r[i] = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
		}
	}

	float Eval(const float x){
		int xi = (int)x;
		int xMin = xi % (int)MAX_VERTICES;
		// TODO: Handle edge cases or values of less than 0
		float t = x - xi;
		// Make function periodic so that ends connect
		int xMax = (xMin == MAX_VERTICES-1) ? 0 : xMin+1;

		// Call function pointer here
		float result = ((*InterpolationFunc)(r[xMin],r[xMax],t));
		return result;
	}

	static const unsigned MAX_VERTICES = 10;
	float r[MAX_VERTICES];
};


struct Color3f{
	float data[3];
	
	float operator[](size_t index){
		return data[index];
	}
};

void GenerateRandPattern() 
{ 
	unsigned imageWidth{};
	unsigned imageHeight{};
	imageWidth = imageHeight = 512; 

	static const unsigned kNumColors = 3; 

	Color3f rockColors[kNumColors] = { 
		{ 0.4078, 0.4078, 0.3764 }, 
		{ 0.7606, 0.6274, 0.6313 }, 
		{ 0.8980, 0.9372, 0.9725 } }; 

	std::ofstream ofs( "./rockpattern.ppm" ); 
	// Write out P6 header
	ofs << "P6\n" << imageWidth << " " << imageHeight << "\n255\n"; 

	for ( int j = 0; j < imageWidth; ++j ){ 
		for ( int i = 0; i < imageHeight; ++i ) { 
			unsigned colorIndex = std::min( unsigned( drand48 () * kNumColors ), kNumColors - 1 ); 
			ofs << 	uint8_t(rockColors[colorIndex][0] * 255) << 
					uint8_t(rockColors[colorIndex][1] * 255) << 
					uint8_t(rockColors[colorIndex][2] * 255); 
		} 
	} 
	ofs.close(); 
}


int main(){

	GenerateRandPattern();

	auto myLerp = [](float a, float b, float t){
		return std::lerp(a,b,t);
	};

	ValueNoise1D<cosineRemap> noise;
//	ValueNoise1D<myLerp> noise;
	for(int i=0; i < 200; ++i){
		float x = i / float(200-1)*10;
		std::cout << "" << x << "," << noise.Eval(x) << std::endl;

	}

	return 0;
}

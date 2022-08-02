// main.d
// Compile with:    dmd ppm.d main.d vec3.d -of=prog
// Run with:        ./prog
import ppm;
import ray;
import vec3;
import sphere;
import utility;
import camera;
import material;

import std.stdio;
import std.conv;
import std.math.traits;
import std.math;
import std.algorithm;




/// Cast a ray out into the screen
/// 'ray' is where the ray is cast
/// world can be a single object or collection to test intersection.
/// depth is the maximum number of 'bounces' for the ray
Vec3 CastRay(Ray r, Hittable world, int depth){
	HitRecord rec = new HitRecord;
	// Check our base case
	if(depth <=0){
		return new Vec3(0,0,0);
	}


	// Note, tMin to 0.0001 to fix shadow 'acne' issue of rays
    //	hitting off of -.00001 instead of t=0
	if(world.Hit(r,0.0001,10000,rec)){
		Ray scattered;
		Vec3 attenuation;
		if(rec.m_material.Scatter(r,rec,attenuation,scattered)){
			return attenuation * CastRay(scattered,world,depth-1);
		}
		else{
			return new Vec3(0,0,0);
		}
	}

	// Draw background sky
    Vec3 unitDirection = r.GetDirection().ToUnitVector();
    auto t = 0.5* (unitDirection.Y() + 1.0);
            // Blend value from start value  to the end value
    return ((1.0-t)*(new Vec3(0.5,0.7,1.0))) + t*(new Vec3(1.0,1.0,1.0));
}


void main(){


	// Create the camera for our scene
	Camera cam = new Camera;
    // Create a PPM image to write to
    PPM ppm = new PPM(cam.GetScreenWidth(),cam.GetScreenHeight());    
	// World
	HittableList world = new HittableList;
	Material ground = new Lambertian(0.0,1.0,0.0);
	world.Add(new Sphere(new Vec3(0,0,-1) 	  ,0.5, new Lambertian(1.0,0.0,0.0)));
	world.Add(new Sphere(new Vec3(0,-100.5,-1),100, ground));

	// Iterate through every pixel one (or multiple times)
	// to generate an image. This is the color of the ray tracer,
	// that shoots out at least one ray per pixel, testing for intersections
	// with an object.
    for(int y=cam.GetScreenHeight()-1; y >=0; --y){
        for(int x= 0; x < cam.GetScreenWidth(); ++x){
            // Cast ray into scene
			// Accumulate the pixel color from multiple samples
			Vec3 pixelColor = new Vec3(0.0,0.0,0.0);
			for(int s= 0; s < cam.GetSamplesPerPixel(); ++s){
				double u = (double(x)+GenerateRandomDouble()) / double(cam.GetScreenWidth()-1);
				double v = (double(y)+GenerateRandomDouble()) / double(cam.GetScreenHeight()-1);
            	Ray r = cam.GetCameraRay(u,v);
				// Accumulate the color
            	pixelColor = pixelColor + CastRay(r,world, cam.GetMaxBounceDepth());
			}
			auto scale = 1.0/ cam.GetSamplesPerPixel();
			double r = clamp( (255*pixelColor[0] * scale), 0,255);
			double g = clamp( (255*pixelColor[1] * scale), 0,255);
			double b = clamp( (255*pixelColor[2] * scale), 0,255);
			// Write out one pixel of information
			ppm.SetPixel(x,y,to!ubyte(r), to!ubyte(g), to!ubyte(b));
        }
    }

    // Write out our scene to a file
    ppm.WriteFile("./output/image.ppm",PPM.MagicNumber.P3,true);
}

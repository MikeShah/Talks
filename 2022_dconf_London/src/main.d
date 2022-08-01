// main.d
// Compile with:    dmd ppm.d main.d vec3.d -of=prog
// Run with:        ./prog
import ppm;
import ray;
import vec3;
import sphere;
import utility;
import camera;

import std.stdio;
import std.conv;
import std.math.traits;
import std.math;
import std.algorithm;




// Cast a ray out into the screen
Vec3 CastRay(Ray r, Hittable world){
	HitRecord rec = new HitRecord;
	if(world.Hit(r,0,10000,rec)){
		Vec3 test = new Vec3(1.0,1.0,1.0);
		return 0.5 * (rec.normal + test);
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
	world.Add(new Sphere(new Vec3(0,0,-1) 	  ,0.5));
	world.Add(new Sphere(new Vec3(0,-100.5,-1),100));

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
            	pixelColor = pixelColor + CastRay(r,world);
			}
			auto scale = 1.0/ cam.GetSamplesPerPixel();
			double r = clamp( (255*pixelColor[0]) * scale, 0,255);
			double g = clamp( (255*pixelColor[1]) * scale, 0,255);
			double b = clamp( (255*pixelColor[2]) * scale, 0,255);
			// Write out one pixel of information
			ppm.SetPixel(x,y,to!ubyte(r), to!ubyte(g), to!ubyte(b));
        }
    }

    // Write out our scene to a file
    ppm.WriteFile("./output/image.ppm",PPM.MagicNumber.P3,true);
}

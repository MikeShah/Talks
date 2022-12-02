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
	HitRecord rec;
	// Check our base case
	if(depth <=0){
		return Vec3(0,0,0);
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
			return Vec3(0,0,0);
		}
	}

	// Draw background sky
    Vec3 unitDirection = r.GetDirection().ToUnitVector();
    auto t = 0.5* (unitDirection.Y() + 1.0);
            // Blend value from start value  to the end value
    return ((1.0-t)*(Vec3(0.5,0.7,1.0))) + t*(Vec3(1.0,1.0,1.0));
}

/// Create a new world from a json file
void LoadWorld(ref HittableList world, string jsonfile){
    import std.file;
    import std.json;
    import std.conv;

    // Setup the materials in our world
    // Could move this to .json file as well!
	Material ground     = new Lambertian(0.6,0.1,0.1);
	Material metal 	    = new Metal(1.0,0.0,0.0);
    Material lambertian = new Lambertian(0.9, 0.6, 0.6);

    // Check if the json file exists
    if(exists(jsonfile)){
        // Read in a text-based file.
        string content = readText(jsonfile);

        // Note: Assume it is a valid .json file, 
        // then parse the json contents
        auto j= parseJSON(content);

        // Find our objects
        if("objects" in j){
            foreach(element; j["objects"].array){
                auto property = element["Sphere"].array;
                Vec3 position = Vec3(property[0].floating,
                                     property[1].floating,
                                     property[2].floating);
                float radius = property[3].floating;

                // Create the object
                if(property[4].str=="Lambertian"){
                    Sphere s = new Sphere(position,radius,lambertian);
                    world.Add(s);
                }
                else if(property[4].str=="metal"){
                    Sphere s = new Sphere(position,radius,metal);
                    world.Add(s);
                }
                else if(property[4].str=="ground"){
                    Sphere s = new Sphere(position,radius,ground);
                    world.Add(s);
                }
            }
        }
    }
}


void main(){


	// Create the camera for our scene
	Camera cam = new Camera;
    // Create a PPM image to write to
    PPM ppm = new PPM(cam.GetScreenWidth(),cam.GetScreenHeight());    
	// World
	HittableList world = new HittableList;
    // Load the file from a .json file
    LoadWorld(world,"./input/world.json");

	// Iterate through every pixel one (or multiple times)
	// to generate an image. This is the color of the ray tracer,
	// that shoots out at least one ray per pixel, testing for intersections
	// with an object.
    import std.parallelism;
    import std.range;
    foreach(y ; cam.GetScreenHeight.iota.parallel){
        foreach(x; cam.GetScreenWidth().iota.parallel){
//    for(int y=cam.GetScreenHeight()-1; y >=0; --y){
//        for(int x= 0; x < cam.GetScreenWidth(); ++x){

            // Cast ray into scene
			// Accumulate the pixel color from multiple samples
			Vec3 pixelColor = Vec3(0.0,0.0,0.0);
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

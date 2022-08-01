// main.d
// Compile with:    dmd ppm.d main.d vec3.d -of=prog
// Run with:        ./prog
import ppm;
import ray;
import vec3;
import sphere;

import std.stdio;
import std.conv;
import std.math.traits;;
import std.math;




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
    // Screen Aspect Ratio
    double aspectRatio 		= 16.0/9.0;
    const uint screenWidth 	= 400;
    const uint screenHeight = to!uint(screenWidth/aspectRatio);
    
	// World
	HittableList world = new HittableList;
	world.Add(new Sphere(new Vec3(0,0,-1) 	  ,0.5));
	world.Add(new Sphere(new Vec3(0,-100.5,-1),100));


    // Camera
    auto viewportHeight = 2.0;
    auto viewportWidth 	= aspectRatio * viewportHeight;
    auto focalLength 	= 1.0;

    auto origin 		 = new Vec3(0.0,0.0,0.0);
    auto horizontal 	 = new Vec3(viewportWidth,0.0,0.0);
    auto vertical   	 = new Vec3(0.0,viewportHeight,0.0);
    auto lowerLeftCorner = origin - (horizontal/2.0) - (vertical/2.0) - (new Vec3(0.0,0.0,focalLength));
    writeln(lowerLeftCorner);

    // Create a PPM image to write to
    PPM ppm = new PPM(screenWidth,screenHeight);    

	// Iterate through every pixel one (or multiple times)
	// to generate an image. This is the color of the ray tracer,
	// that shoots out at least one ray per pixel, testing for intersections
	// with an object.
    for(int y=screenHeight-1; y >=0; --y){
        for(int x= 0; x < screenWidth; ++x){
            double u = double(x) / double(screenWidth-1);
            double v = double(y) / double(screenHeight-1);
            // Cast ray into scene
            Ray r = new Ray(origin,lowerLeftCorner + u*horizontal + v*vertical - origin);
            // Determine the pixel color
            Vec3 pixelColor = CastRay(r,world);
			// Write out one pixel of information
			ppm.SetPixel(x,y,to!ubyte(255*pixelColor[0]),
						 	 to!ubyte(255*pixelColor[1]),
						 	 to!ubyte(255*pixelColor[2]));
        }
    }

    // Write out our scene to a file
    ppm.WriteFile("./output/image.ppm",PPM.MagicNumber.P3,true);
}

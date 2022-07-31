// main.d
// Compile with:    dmd ppm.d main.d vec3.d -of=prog
// Run with:        ./prog
import ppm;
import ray;
import vec3;

import std.stdio;
import std.conv;
import std.math.traits;;

bool HitSphere(Vec3 center, double radius, Ray r){
    Vec3 oc = r.GetOrigin() - center;
    
    double a = DotProduct(r.GetDirection(), r.GetDirection());
    double b = 2.0 * DotProduct(oc, r.GetDirection());
    double c = DotProduct(oc,oc) - radius*radius;
    double discriminat = b*b - 4*a*c;

    return (discriminat > 0);
}


// Cast a ray out into the screen
Vec3 CastRay(Ray r){
    if(HitSphere(new Vec3(0,0,-1),0.5,r)){
        return (new Vec3(0.0,0.0,1.0));
    }

    Vec3 unitDirection = r.GetDirection().ToUnitVector();
    auto t = 0.5* (unitDirection.Y() + 1.0);
            // Blend value from start value  to the end value
    return ((1.0-t)*(new Vec3(0.5,0.7,1.0))) + t*(new Vec3(1.0,1.0,1.0));
}


void main(){
    // Screen Aspect Ratio
    double aspectRatio = 16.0/9.0;
    const uint screenWidth = 400;
    const uint screenHeight = to!uint(screenWidth/aspectRatio);
    
    // Camera
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    auto origin = new Vec3(0.0,0.0,0.0);
    auto horizontal = new Vec3(viewportWidth,0.0,0.0);
    auto vertical   = new Vec3(0.0,viewportHeight,0.0);
    auto lowerLeftCorner = origin - horizontal/2.0 - vertical/2.0 - (new Vec3(0.0,0.0,focalLength));
    writeln(lowerLeftCorner);

    // Create a PPM image to write to
    PPM ppm = new PPM(screenWidth,screenHeight);    

    for(int y=screenHeight-1; y >=0; --y){
        for(int x= 0; x < screenWidth; ++x){
            double u = double(x) / double(screenWidth-1);
            double v = double(y) / double(screenHeight-1);
            if(isNaN(u)){
                writeln("UUUUUUUUUUU");
            }
            if(isNaN(v)){
                writeln("VVVVVVVVVVVV");
            }
            // Cast ray into scene

            Ray r = new Ray(origin,lowerLeftCorner + u*horizontal + v*vertical - origin);
            // Determine the pixel color
            Vec3 pixelColor = CastRay(r);
            if(isNaN(pixelColor[0]) || isNaN(pixelColor[1]) || isNaN(pixelColor[2])){
/*
                ppm.SetPixel(x,y,0,255,0); 
                writeln(u);
                writeln(v);
                writeln(lowerLeftCorner + u*horizontal + v*vertical - origin);
                writeln(pixelColor);
                writeln(r);
*/
            }else{
                // Write out one pixel of information
                ppm.SetPixel(x,y,to!ubyte(255*pixelColor[0]),
                                 to!ubyte(255*pixelColor[1]),
                                 to!ubyte(255*pixelColor[2]));
            }
        }
    }

    // Write out our scene
    ppm.WriteFile("./output/image.ppm",PPM.MagicNumber.P3);
}



import vec3;

struct HitRecord{
    Vec3 p;
    Vec3 normal;
    double t;
}

interface Hittable{
    bool Hit(Ray r, double tMin, double tMax, HitRecord rec);
}

class Sphere : HitRecord{
    /// Constructor
    this(){
        
    }

    bool Hit(Ray r, double tMin, double tMax, HitRecord rec);
        Vec3 oc = r.GetOrigin() - center;
        
        double a = DotProduct(r.GetDirection(), r.GetDirection());
        double b = 2.0 * DotProduct(oc, r.GetDirection());
        double c = DotProduct(oc,oc) - radius*radius;
        double discriminant = b*b - 4*a*c;
        if(discriminant < 0){
            return -1.0;
        }else{
            return (-b - sqrt(discriminant)) / (2.0 *a);
        }
    }

}



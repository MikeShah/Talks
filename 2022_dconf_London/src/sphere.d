module sphere;

import vec3;
import ray;
import material;

import std.math;

class HitRecord{
    Vec3 p;
    Vec3 normal;
    double t;
	bool front_face;
	Material m_material; // This property tells us how to interact when rays intersect this surface.
	// TODO: Rename member variables

	void SetFaceNormal(ref Ray r, ref Vec3 outwardNormal){
		front_face = DotProduct(r.GetDirection(), outwardNormal) < 0;
	   	normal = front_face ? outwardNormal : -outwardNormal;	
	}
}

interface Hittable{
    bool Hit(Ray r, double tMin, double tMax, ref HitRecord rec);
}

class HittableList : Hittable{
	/// Default constructor
	this(){
	}	

	/// Add a new object to our dynamic array of objects
	/// 
	void Add(Hittable obj){
		m_objects ~= obj;
	}
	
	/// Clear all of our objects
	void ClearAll(){
		// TODO:	
	}

    override bool Hit(Ray r, double tMin, double tMax, ref HitRecord rec){
		HitRecord tempRec = new HitRecord;
		bool hitAnything = false;
		auto closestSoFar = tMax;

		foreach (element ; m_objects){
			if(element.Hit(r,tMin,closestSoFar, tempRec)){
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec;
			}
		}	

		return hitAnything;
	}

	/// Member variables
	private Hittable[] m_objects;

}

class Sphere : Hittable{
    /// Constructor
    this(){ 
		m_center = new Vec3;
		m_radius = 0.0;
		m_material = new Lambertian(1.0,0.0,0.0); // Create a default material
    }

	this(Vec3 center, double radius, Material material){
		m_center = new Vec3(0.0,0.0,0.0);

		m_center = center;
		m_radius = radius;
		m_material = material;
	}

    bool Hit(Ray r, double tMin, double tMax, ref HitRecord rec){
        Vec3 oc = r.GetOrigin() - m_center;
		auto a = r.GetDirection().LengthSquared();
		auto half_b = DotProduct(oc,r.GetDirection());
        double c = oc.LengthSquared() - m_radius*m_radius;


		auto discriminant = half_b*half_b - a * c;
        if(discriminant< 0){
            return false;
		}

		auto sqrtdeterminant = sqrt(discriminant);

		// Fid the nearest root that lies in the acceptable range
        auto root = (-half_b - sqrtdeterminant) / a;
		if(root < tMin || tMax < root){
			root = (-half_b + sqrtdeterminant) / a;
			if(root < tMin || tMax < root){
				return false;
			}
		}

		rec.t 				= root;
		rec.p 				= r.At(rec.t);
		Vec3 outwardNormal 	= new Vec3;
		outwardNormal 		= (rec.p - m_center) / m_radius;
		rec.SetFaceNormal(r,outwardNormal);
		rec.m_material = m_material;

		// A hit was successfully made
		return true;
    }

	private Material m_material;
	private Vec3 m_center;
	private double m_radius;
}



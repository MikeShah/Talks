module material;

import sphere;
import vec3;
import ray;
import utility;

interface Material{
	bool Scatter(ref Ray r, HitRecord rec, ref Vec3 attenuation, ref Ray scattered);
}

class Lambertian : Material{
	this(double r, double g, double b){
		m_albedo = Vec3(r,g,b);
	}
	this(Vec3 color){
		m_albedo = color;
	}

	override bool Scatter(ref Ray r, HitRecord rec, ref Vec3 attenuation, ref Ray scattered){
		auto scatterDirection = rec.normal + GenerateRandomVec3();

		if(scatterDirection.IsZero()){
			scatterDirection = rec.normal;
		}

		scattered = new Ray(rec.p, scatterDirection);
		attenuation = m_albedo;
		return true;
	}

	private Vec3 m_albedo;
}


class Metal : Material{
	this(double r, double g, double b){
		m_albedo = Vec3(r,g,b);
	}
	this(Vec3 color){
		m_albedo = color;
	}

	override bool Scatter(ref Ray r, HitRecord rec, ref Vec3 attenuation, ref Ray scattered){
		Vec3 reflected = Reflect(r.GetDirection().ToUnitVector(), rec.normal);
		scattered = new Ray(rec.p, reflected);
		attenuation = m_albedo;
	
		return (DotProduct(scattered.GetDirection(), rec.normal) > 0);
	}

	private Vec3 m_albedo;
}

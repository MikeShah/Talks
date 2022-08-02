module camera;

import ray;
import vec3;

import std.conv;

class Camera{
	/// Constructor
	this(){
		// Screen Aspect Ratio
		m_aspectRatio 		= 16.0/9.0;
		m_screenWidth 	= 1920;
		m_screenHeight = to!uint(m_screenWidth/m_aspectRatio);
		
		// Quality Settings
		m_samplesPerPixel 	= 50;
		m_bounceDepth 		= 50;
		
		// Camera
		auto viewportHeight = 2.0;
		auto viewportWidth 	= m_aspectRatio * viewportHeight;
		auto focalLength 	= 1.0;

		m_origin 		 = Vec3(0.0,0.0,0.0);
		m_horizontal 	 = Vec3(viewportWidth,0.0,0.0);
		m_vertical   	 = Vec3(0.0,viewportHeight,0.0);
		m_lowerLeftCorner = m_origin - (m_horizontal/2.0) - (m_vertical/2.0) - (Vec3(0.0,0.0,focalLength));
	}

		/// Cast a ray from the camera
		Ray GetCameraRay(float u, float v){
			auto dir = m_lowerLeftCorner + u*m_horizontal + v*m_vertical - m_origin;
			return Ray(m_origin, dir.Normalized);
		}

		/// Retrieve the screen Width
		uint GetScreenWidth() const{
			return m_screenWidth;
		}

		/// Retrieve the screen Height
		uint GetScreenHeight() const{
			return m_screenHeight;
		}

		/// samples used for anti-aliasing
		uint GetSamplesPerPixel() const{
			return m_samplesPerPixel;
		}

		/// How many times a ray can 'bounce'
		uint GetMaxBounceDepth() const{
			return m_bounceDepth;
		}

		/// Private member variables
		private Vec3 m_origin;		 
		private Vec3 m_horizontal; 	 
		private Vec3 m_vertical; 	 
		private Vec3 m_lowerLeftCorner; 

		// Image quality
		private uint m_samplesPerPixel; 
		private uint m_bounceDepth; 

		private const uint m_screenWidth;	
		private const uint m_screenHeight; 
		private float m_aspectRatio;
}

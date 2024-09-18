
import image;

struct Material{
	string mMaterialName;
	float Ns;
	float[3] Ka;
	float[3] Ks;
	float[3] Ke;
	float Ni;
	float d;
	float illum;
	Image mDiffuseImage;
	Image mBumpImage;

	this(string materialName){
		mMaterialName = materialName;
	}
	~this(){

	}

}

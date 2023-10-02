#pragma once
#include <string>
class Image{
	public:
		// Forward Declaration that can be overriden
		virtual void LoadImage(std::string filename);
		// ...

	private:
		std::string filename;
		std::string extension;
};

class Bitmap : public Image{
	public:
		void LoadImage(std::string filename) override;	
};

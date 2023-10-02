#pragma once
#include <string>
class Image{
	public:
		// Forward Declaration
		void LoadImage(std::string filename);
		// ...

	private:
		std::string filename;
		std::string extension;
};

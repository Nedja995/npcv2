#include "npcv/filters/ProcessGray.h"
#include "npcv/types/Image.h"
#include <iostream>
#include <math.h>

namespace npcv { namespace processing {


	void ProcessGray::processImage()
	{
		divideImagePixels(_image, _intensity);
	}

	int ProcessGray::getIntensity()
	{
		return _intensity;
	}

	void ProcessGray::setIntensity(int value)
	{
		_intensity = value;
	}

	bool ProcessGray::divideImagePixels(Image * image, int intensity)
	{
		if (image == 0) {
			std::cerr << "npcv: ProcessGray::divideImagePixels: NULL image" << std::endl;
			return false;
		}
		uchar* pixels = image->pixels;
		int pixelsMax = image->width * image->height * image->type;
		for (int pxIndex = 0; pxIndex < pixelsMax; pxIndex += image->type)
		{

			*(pixels + pxIndex + 2) /= 2;
			*(pixels + pxIndex + 1) /= 2;
			*(pixels + pxIndex) /= 2;
		}

		return false;
	}


	bool ProcessGray::divideImagePixels2(Image * image, int intensity)
	{
		if (image == 0) {
			std::cerr << "npcv: ProcessGray::divideImagePixels: NULL image" << std::endl;
			return false;
		}
		uchar* pixels = image->pixels;
		int pixelsMax = image->width * image->height * image->type;
		for (int pxIndex = 0; pxIndex < pixelsMax; pxIndex += image->type)
		{

			*(pixels + pxIndex + 2) /= 2;
			*(pixels + pxIndex + 1) /= 2;
			*(pixels + pxIndex) /= 2;
		}

		return false;
	}


}
}
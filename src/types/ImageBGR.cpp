#include "npcv/types/ImageBGR.h"

namespace npcv {
	namespace types {



		ImageBGR::ImageBGR(ImageBGR & image)
		{
		}

		ImageBGR::ImageBGR(uchar * data, int width, int height)
			: _data(data)
			, _width(width)
			, _height(height)
		{	
		}

		ImageBGR::~ImageBGR()
		{
			
		}

		void * ImageBGR::getData()
		{
			return (void*)_data;
		}

		ulint ImageBGR::getMemSize()
		{
			return ulint();
		}

		int ImageBGR::getWidth()
		{
			return _width;
		}

		int ImageBGR::getHeight()
		{
			return _height;
		}

		ImageType ImageBGR::getType()
		{
			return ImageType::BGR;
		}

		Pixel * ImageBGR::getPixels()
		{
			return nullptr;
		}
	}
}
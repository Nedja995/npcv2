#include "npcv/filters/IPBlending.h"
#include <iostream>
namespace npcv {
	namespace processing {



		IPBlending::IPBlending(Image * first, Image * second)
			: IPBlending()
		{
			_image = first;
			_imageSecond = second;
		}

		IPBlending::IPBlending()
		{
			_image = 0;
			_imageSecond = 0;
			_initialized = false;
		}


		IPBlending::~IPBlending()
		{
		}

		void IPBlending::setSecondImage(Image * image)
		{
			_imageSecond = image;
		}

		Image * IPBlending::getSecondImage()
		{
			return _imageSecond;
		}

		void IPBlending::processImage()
		{
			_processing = true;
			Blend(_image, _imageSecond, ratio);
			_processing = false;
		}
		void IPBlending::initialize()
		{
			IProcessImage::initialize();
			if (_imageSecond == 0) {
				std::cerr << "npcv:IPBlending::initialize: missing second image" << std::endl;
				_initialized = false;
			}
			//check sizes
			if (_image->width != _imageSecond->width
				|| _image->height != _imageSecond->height
				|| _image->type != _imageSecond->type)
			{
				std::cerr << "npcv:IPBlending::initialize: image are is same size or type" << std::endl;
				_initialized = false;
			}
		}

	}
}
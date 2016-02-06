#include "npcv/processes/IProcessImage.h"

#include <iostream>
namespace npcv {
	namespace processing {


		//using namespace types;


		IProcessImage::~IProcessImage()
		{
		}

		void IProcessImage::initialize()
		{
			_initialized = true;
		}

		bool IProcessImage::isInitialized()
		{
			return _initialized;
		}

		void IProcessImage::execute()
		{
			if (!isInitialized()) {
				std::cerr << "npcv: IProcessImage::execute: not initialized" << std::endl;
				return;
			}
			processImage();
		}

		bool IProcessImage::isProcessing()
		{
			return _processing;
		}

		void IProcessImage::free()
		{
		}

		IProcessImage::IProcessImage()
		{
		}

		Image * IProcessImage::getImage()
		{
			return _image;
		}

		void IProcessImage::setImage(Image * image)
		{
			_image = image;
		}



	}
}
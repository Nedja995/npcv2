#include "../include/controlls/ImageBox.h"
#include "npcv/utils/ImageStreamSTB.h"
#include "../thirdparty/include/thirdparty/stb/stb_image.h"
namespace npcvGui
{

	ImageBox::Ptr ImageBox::Create()
	{
		return Ptr(new ImageBox());
	}

	ImageBox::~ImageBox()
	{
	}

	npcv::Image * ImageBox::getCVImage()
	{
		int width, height, type;
		unsigned char* imageData = stbi_load_from_memory(imageFile, imageSizeBytes, &width, &height, &type, 0);
		if (imageData == 0) {
			std::cerr << "npcvGui:ImageBox:getCVImage: can't load image from memory" << std::endl;
			return 0;
		}
		return new npcv::Image(imageData, width, height, (npcv::PixelType)type);
	}


	bool ImageBox::load(unsigned char * imageInMemory, size_t sizeBytes)
	{
		int width, height, type;
		unsigned char* imageData = stbi_load_from_memory(imageInMemory, imageSizeBytes, &width, &height, &type, 0);
		//sfImage->load
		return false;
	}

	bool ImageBox::reload()
	{
		//first check memory for image to show
		if (imageFile) {
			// Load from memory
		}
		else {
			return false;
		}

		return true;
	}

	void ImageBox::init()
	{
		// Create and Init ImageInspecotr
		_inspectorBox = ImageInspectorBox::Create();
		_inspectorBox->init();
		// Create widgets
		sgMainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
		sgImage = sfg::Image::Create();

		// Configure widgets

		// Pack widgets
		sgMainBox->Pack(sgImage);
		sgMainBox->Pack(_inspectorBox->sgMainBox);
	}
}
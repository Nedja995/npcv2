#include "../include/controlls/ImageBox.h"
#include "npcv/utils/ImageStreamSTB.h"
#include "../thirdparty/include/thirdparty/stb/stb_image.h"
#include "../thirdparty/include/thirdparty/stb/stb_image_write.h"
#include "npcv/Toolset.h"

extern unsigned char *stbi_write_png_to_mem(unsigned char *pixels, 
											int stride_bytes,
											int x, int y, int n, 
											int *out_len);

namespace npcvGui
{


	ImageBox::~ImageBox()
	{
	}

	npcv::Image* ImageBox::getCVImage()
	{
		int width, height, type;
		unsigned char* imageData = stbi_load_from_memory(imageFile, imageSizeBytes, &width, &height, &type, 0);
		if (imageData == 0) {
			std::cerr << "npcvGui:ImageBox:getCVImage: can't load image from buffer" << std::endl;
			return 0;
		}
		return new npcv::Image(imageData, width, height, (npcv::PixelType)type);
	}


	bool ImageBox::load(const char * imagePath)
	{
		npImage = npcv::Toolset::SharedInstance()->imageStream->Load(imagePath);
		return load(npImage);
	}

	bool ImageBox::load(npcv::Image * npImage)
	{
		int imgFileSize;
		unsigned char* imgFile = stbi_write_png_to_mem(npImage->pixels, 0, npImage->width, npImage->height, npImage->type, &imgFileSize);
		if (imgFile == 0) {
			std::cerr << "npcvGui:ImageBox:load: cannot write image to buffer" << std::endl;
			return false;
		}
		return load(imgFile, imgFileSize);;
	}

	
	bool ImageBox::load(unsigned char * imageInMemory, size_t sizeBytes)
	{
		sf::Image sfImage;
		if (sfImage.loadFromMemory(imageInMemory, sizeBytes)) {
			//sgImage = sfg::Image::Create(sfImage);
			sgResizableImage = sfg::ResizableImage::Create(sfImage);
			sgResizableImage->Resize(100, 100);
			sgImage->SetImage(sgResizableImage->GetResizedImage());

		}
		else {
			std::cerr << "npcvGui:ImageBox:load: cannot load image from buffer" << std::endl;
			return false;
		}
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

	void ImageBox::resize(float x, float y)
	{
	//	sgResizableImage->Resize(x, y);
		sgImage->SetImage(sgResizableImage->GetResizedImage());
	}

	void ImageBox::_onResize()
	{

	}


	void ImageBox::init()
	{
		// Create and Init ImageInspecotr
		_inspectorBox = new npcvGui::ImageInspectorBox(this);
		_inspectorBox->init();

		// Create widgets
		sgMainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
		sgImage = sfg::Image::Create();
		
		// Configure widgets

		// Pack widgets
		sgMainBox->Pack(sgImage);
		sgMainBox->Pack(_inspectorBox->sgMainBox);
	
		// Configure listeners
		sgMainBox->GetSignal( sfg::Widget::OnStateChange).Connect(std::bind(&ImageBox::_onResize, this));
	
	}
	ImageBox::ImageBox()
	{
	}
}
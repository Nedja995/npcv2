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
			this->imageSizeBytes = sizeBytes;
			imageFile = (unsigned char*) malloc(sizeBytes);
			memcpy(imageFile, imageInMemory, sizeBytes);
			sgResizableImage = sfg::ResizableImage::Create(sfImage);
			refresh();

		}
		else {
			std::cerr << "npcvGui:ImageBox:load: cannot load image from buffer" << std::endl;
			return false;
		}
		return false;
	}



	bool ImageBox::refresh()
	{
		//first check memory for image to show
		if (sgResizableImage->GetResizedImage().getPixelsPtr() != 0) {
			sgImage->SetImage(sgResizableImage->GetResizedImage());
		}
		else if (sgResizableImage->GetImage().getPixelsPtr() != 0) {
			sgImage->SetImage(sgResizableImage->GetImage());
		}
		else {
			return false;
		}

		return true;
	}

	void ImageBox::_onResize()
	{

	}

	npcv::Image * ImageBox::GetProcessedImageNp()
	{
		return nullptr;
	}

	sfg::Image::Ptr ImageBox::GetProcessedImageSfg()
	{
		return sfg::Image::Ptr();
	}

	npcv::Image * ImageBox::GetImageNp()
	{
		if (npImage != 0) {
			return npImage;
		}
		
		npImage = new npcv::Image();
		npImage->loadFromMemory(imageFile, imageSizeBytes);
		return npImage;
	}

	sfg::Image::Ptr ImageBox::GetImageSfg()
	{
		return sfg::Image::Ptr();
	}

	void ImageBox::resize(float x, float y)
	{
		int newWidth = sgResizableImage->GetImage().getSize().x * x;
		int newHeight = sgResizableImage->GetImage().getSize().y * y;
		sgResizableImage->Resize(newWidth, newHeight);
		sgImage->SetImage(sgResizableImage->GetResizedImage());
	}



	void ImageBox::init()
	{
		// Create and Init ImageInspecotr
		_inspectorBox = new npcvGui::ImageInspectorBox(this);
		_inspectorBox->init();

		// Create widgets
		sgMainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
		sgImage = sfg::Image::Create();
		auto table = sfg::Table::Create();
		auto m_scrolled_window_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
		auto scrolledwindow = sfg::ScrolledWindow::Create();
		auto alignment = sfg::Alignment::Create();
		auto alignment_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
		
		// Configure widgets
		scrolledwindow->SetScrollbarPolicy(sfg::ScrolledWindow::HORIZONTAL_ALWAYS | sfg::ScrolledWindow::VERTICAL_AUTOMATIC);
		scrolledwindow->AddWithViewport(m_scrolled_window_box);
		scrolledwindow->SetRequisition(sf::Vector2f(500.f, 100.f));
		alignment_box->Pack(alignment, true, true);
		alignment->SetScale(sf::Vector2f(1.0f, .0f));
		alignment->SetAlignment(sf::Vector2f(.1f, .1f));


		// Pack widgets
		m_scrolled_window_box->Pack(sgImage);
		alignment->Add(_inspectorBox->sgMainBox);
		table->Attach(scrolledwindow, sf::Rect<sf::Uint32>(0, 0, 4, 4));
		table->Attach(alignment, sf::Rect<sf::Uint32>(0, 4, 4, 1));
		sgMainBox->Pack(table);

		// Configure listeners
		sgMainBox->GetSignal( sfg::Widget::OnStateChange).Connect(std::bind(&ImageBox::_onResize, this));
	
	}
	ImageBox::ImageBox()
		: npImage(0)
	{
	}
}
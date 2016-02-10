#pragma once
#include "npcv/types/Image.h"
#include "npcv/utils/ResourceManager.h"
#include "../include/controlls/ResizableImage.h"

#include "IImageGUI.h"
#include "ImageInspectorBox.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

namespace npcvGui
{
	class ImageInspectorBox;
	class ImageBox : public IImageGUI
	{
	public:
		void init();
		ImageBox();
		~ImageBox();

		sfg::Box::Ptr sgMainBox;
		
		npcv::Image* getCVImage();

		unsigned char* imageFile;

		size_t imageSizeBytes;



		//void resize(float x, float y);
		// Inherited via IImageGUI
		virtual bool load(const char * imagePath) override;
		virtual bool load(npcv::Image * npImage) override;
		virtual bool load(unsigned char * imageFile, size_t sizeBytes) override;
		virtual void resize(float x, float y) override;
		virtual bool refresh() override;


	protected:
		npcv::Image* npImage;

		void _onResize();



	private:
		sfg::Image::Ptr sgImage;
		sfg::ResizableImage::Ptr sgResizableImage;
		// Image Inspector
		npcvGui::ImageInspectorBox* _inspectorBox;

		// Inherited via IImageGUI
		virtual npcv::Image * GetProcessedImageNp() override;
		virtual sfg::Image::Ptr GetProcessedImageSfg() override;
		virtual npcv::Image * GetImageNp() override;
		virtual sfg::Image::Ptr GetImageSfg() override;
	};


}
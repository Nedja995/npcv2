#pragma once
#include "npcv/types/Image.h"
#include "npcv/utils/ResourceManager.h"
#include "../include/controlls/ResizableImage.h"

#include "ImageInspectorBox.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

namespace npcvGui
{
	class ImageInspectorBox;
	class ImageBox
	{
	public:
		void init();
		ImageBox();
		~ImageBox();

		sfg::Box::Ptr sgMainBox;
		
		npcv::Image* getCVImage();

		unsigned char* imageFile;

		size_t imageSizeBytes;

		bool load(const char* imagePath);
		bool load(npcv::Image* npImage);
		bool load(unsigned char* imageFile, size_t sizeBytes);
		
		bool reload();

		void resize(float x, float y);

	protected:
		npcv::Image* npImage;

		void _onResize();



	private:
		sfg::Image::Ptr sgImage;
		sfg::ResizableImage::Ptr sgResizableImage;
		// Image Inspector
		npcvGui::ImageInspectorBox* _inspectorBox;

	};

	class ImageInspectorBox
	{
	public:
		/*typedef std::shared_ptr<ImageInspectorBox> Ptr;
		static Ptr Create();*/
		ImageInspectorBox(npcvGui::ImageBox* parentImageBox);
		~ImageInspectorBox();

		sfg::Box::Ptr sgMainBox;

		void init();

		void setParent(npcvGui::ImageBox* imageBox);

	protected:
		void _onLoadClick();



		npcvGui::ImageBox* _parentImageBox;
		sfg::Entry::Ptr _inputEntry;
		sfg::Label::Ptr _widthLabel;
		sfg::Label::Ptr _heightLabel;

	};

}
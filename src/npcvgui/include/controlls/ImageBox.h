#pragma once
#include "npcv/types/Image.h"
#include "ImageInspectorBox.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
namespace npcvGui
{
	class ImageBox
	{
	public:
		typedef std::shared_ptr<ImageBox> Ptr;
		static Ptr Create();
		void init();
		~ImageBox();

		sfg::Box::Ptr sgMainBox;
		
		npcv::Image* getCVImage();
		unsigned char* imageFile;
		size_t imageSizeBytes;

		bool load(unsigned char* imageFile, size_t sizeBytes);
		bool reload();

	private:
		sfg::Image::Ptr sgImage;
		
		// Image Inspector
		ImageInspectorBox::Ptr _inspectorBox;

	};

}
#pragma once
#include <SFGUI/Widgets.hpp>
#include "IImageGUI.h"

namespace npcvGui
{
	class ImageInspectorBox
	{
	public:
		/*typedef std::shared_ptr<ImageInspectorBox> Ptr;
		static Ptr Create();*/
		ImageInspectorBox(npcvGui::IImageGUI* parentImageBox);
		~ImageInspectorBox();

		sfg::Box::Ptr sgMainBox;

		void init();

		void setParent(npcvGui::IImageGUI* imageBox);
		
	protected:
		void _onLoadClick();
		void _onBrowseClick();
		void _onZoomChange();
		void _onProcessClick();


		npcvGui::IImageGUI* _parentImageBox;
		sfg::Entry::Ptr _inputEntry;
		sfg::Label::Ptr _widthLabel;
		sfg::Label::Ptr _heightLabel;

		sfg::Scale::Ptr _zoomScale;
	};

}
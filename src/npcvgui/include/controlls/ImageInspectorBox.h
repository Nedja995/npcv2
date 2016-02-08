#pragma once
#include <SFGUI/Widgets.hpp>
namespace npcvGui
{
	class ImageInspectorBox
	{
	public:
		typedef std::shared_ptr<ImageInspectorBox> Ptr;
		static Ptr Create();
		~ImageInspectorBox();

		sfg::Box::Ptr sgMainBox;

		void init();

	private:
		sfg::Entry::Ptr _inputEntry;
		sfg::Label::Ptr _widthLabel;
		sfg::Label::Ptr _heightLabel;

	};

}
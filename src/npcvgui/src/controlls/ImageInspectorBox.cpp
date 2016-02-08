#include "../include/controlls/ImageInspectorBox.h"



namespace npcvGui
{
	ImageInspectorBox::Ptr ImageInspectorBox::Create()
	{
		return Ptr(new ImageInspectorBox());
	}

	ImageInspectorBox::~ImageInspectorBox()
	{
	}

	void ImageInspectorBox::init()
	{
		// Create widgets
		sgMainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
		_inputEntry = sfg::Entry::Create();
		_widthLabel = sfg::Label::Create("width");
		_heightLabel = sfg::Label::Create("height");
		auto frame = sfg::Frame::Create();
		auto table = sfg::Table::Create();
		auto browseButton = sfg::Button::Create("Browse");
		auto loadButton = sfg::Button::Create("Load");

		// Configure widgets
		table->SetColumnSpacings(5.f);
		table->SetRowSpacings(5.f);
		_inputEntry->SetRequisition(sf::Vector2f(80.f, 0.f));
	
		// Pack widgets
		table->Attach(_inputEntry, sf::Rect<sf::Uint32>(0, 0, 3, 1));
		table->Attach(browseButton, sf::Rect<sf::Uint32>(3, 0, 1, 1));
		table->Attach(loadButton, sf::Rect<sf::Uint32>(4, 0, 1, 1));
		table->Attach(_widthLabel, sf::Rect<sf::Uint32>(0, 1, 1, 1), sfg::Table::FILL, sfg::Table::FILL);
		table->Attach(_heightLabel, sf::Rect<sf::Uint32>(1, 1, 1, 1));
		frame->Add(table);
		sgMainBox->Pack(frame);
	}

}
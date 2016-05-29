//#include "widgets/ImageInspectorBox.h"
#include "NpcvGUI.h"
#include "npcv/Toolset.h"
#include "widgets/ImageBox.h"

#include "npcv/abs/IDialogFileSelect.h"

#include "npcv/processes/IPMatrixApply.h"

namespace npcvGui
{


	ImageInspectorBox::ImageInspectorBox(IImageGUI* parentImageBox)
		: _parentImageBox(parentImageBox)
	{

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
		_zoomScale = sfg::Scale::Create(sfg::Scale::Orientation::HORIZONTAL);
		auto frame = sfg::Frame::Create();
		auto table = sfg::Table::Create();
		auto browseButton = sfg::Button::Create("Browse");
		auto loadButton = sfg::Button::Create("Load");
		auto processButton = sfg::Button::Create("Process");


		// Configure widgets
		table->SetColumnSpacings(5.f);
		table->SetRowSpacings(5.f);
		_inputEntry->SetRequisition(sf::Vector2f(10.0f, 15.0f));
		_zoomScale->SetRequisition(sf::Vector2f(10.0f, 15.0f));
		_zoomScale->SetValue(1.0f);
		auto zoomAdj = _zoomScale->GetAdjustment();
		zoomAdj->SetLower(0.1f);
		zoomAdj->SetUpper(5.0f);
		zoomAdj->SetMinorStep(0.1f);
		zoomAdj->SetMajorStep(0.1f);
	
		// Pack widgets
		table->Attach(_zoomScale, sf::Rect<sf::Uint32>(0, 0, 4, 1));
		table->Attach(_inputEntry, sf::Rect<sf::Uint32>(0, 1, 3, 1));
		table->Attach(browseButton, sf::Rect<sf::Uint32>(3, 1, 1, 1));
		table->Attach(loadButton, sf::Rect<sf::Uint32>(4, 1, 1, 1));
		table->Attach(_widthLabel, sf::Rect<sf::Uint32>(0, 2, 1, 1), sfg::Table::FILL, sfg::Table::FILL);
		table->Attach(_heightLabel, sf::Rect<sf::Uint32>(1, 2, 1, 1));
		table->Attach(processButton, sf::Rect<sf::Uint32>(0, 3, 1, 1));
		frame->Add(table);
		sgMainBox->Pack(frame);

		// Listeners
		loadButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ImageInspectorBox::_onLoadClick, this));
		browseButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ImageInspectorBox::_onBrowseClick, this));
		zoomAdj->GetSignal( sfg:: Adjustment::OnChange ).Connect(std::bind(&ImageInspectorBox::_onZoomChange, this));
		processButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ImageInspectorBox::_onProcessClick, this));
	}

	void ImageInspectorBox::setParent(IImageGUI* imageBox)
	{
		_parentImageBox = imageBox;
	}

	void ImageInspectorBox::_onLoadClick()
	{
		_parentImageBox->load(_inputEntry->GetText().toAnsiString().c_str());
		
		//npcvGui::NpcvGUI::Instance()->getResourceManager()
	}

	void ImageInspectorBox::_onBrowseClick()
	{
		auto dialog = npcv::Toolset::SharedInstance()->uiDialogFileselect();
		dialog->show();
		auto path = dialog->getPathSelected();
		std::cout << "HEre it is: " << path << std::endl;
		_inputEntry->SetText(sf::String(path->c_str()));
	}

	void ImageInspectorBox::_onZoomChange()
	{
		auto val = _zoomScale->GetValue();
		_parentImageBox->resize(val, val);
		_parentImageBox->refresh();
	}

	void ImageInspectorBox::_onProcessClick()
	{
		auto matrixProc = new npcv::processing::IPMatrixApply();
		matrixProc->setImage(new npcv::Image(_parentImageBox->GetImageNp()));
		int matrixSize = 3;

		matrixProc->matrixSize = matrixSize;
		float filter[9] =
		{
			1,  1,  1,
			1, -7,  1,
			1,  1,  1
		};
		matrixProc->matrix = &filter[0];
		/*matrixProc->bias = ;
		matrixProc->factor = ;*/

		matrixProc->initialize(); //initialize
		matrixProc->execute();
		_parentImageBox->load(matrixProc->getImage());
	}

}
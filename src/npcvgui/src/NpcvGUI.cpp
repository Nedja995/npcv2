#include "../include/NpcvGUI.h"
#include "../include/controlls/ImageBox.h"
#include "../include/npcv/utils/ImageStreamSTB.h"
#include "../include/npcv/utils/ResourceManager.h"

#include "../include/controlls/WinMatrixFilter.h"

namespace npcvGui {
	const unsigned int NpcvGUI::SCREEN_WIDTH = 800;
	const unsigned int NpcvGUI::SCREEN_HEIGHT = 600;



	NpcvGUI::NpcvGUI() :
		m_desktop(),
		m_window(sfg::Window::Create()),
		m_count(0)
	{
		setResourceManager(new npcv::ResourceManager(std::string("D:\\Projects\\npcv2\\samples\\data")));
	}

	NpcvGUI::~NpcvGUI()
	{
	}

	void NpcvGUI::_onResize() {
		std::cout << "fdsf";
	}

	void NpcvGUI::Run() {
		sf::RenderWindow render_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFGUI Desktop Example");
		sf::Event event;

		// We have to do this because we don't use SFML to draw.
		render_window.resetGLStates();

		// Init.
		m_desktop.SetProperty("Button#create_window", "FontSize", 18.f);

		//// Main window ////
		// Widgets.
		m_window->SetTitle("SFGUI Desktop Example");

		auto intro_label = sfg::Label::Create("Click on \"Create window\" to create any number of new windows.");
		auto create_window_button = sfg::Button::Create("Create window");
		create_window_button->SetId("create_window");

		// Layout.
		auto main_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
		main_box->Pack(intro_label, false);
		main_box->Pack(create_window_button, false);

		m_window->Add(main_box);
		m_desktop.Add(m_window);

		// Signals.
		create_window_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&NpcvGUI::OnCreateWindowClick, this));

		while (render_window.isOpen()) {
			while (render_window.pollEvent(event)) {
				if (
					(event.type == sf::Event::Closed) ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
					) {
					render_window.close();
				}
				else {
					m_desktop.HandleEvent(event);
				}
			}

			///////
			//auto rect = m_window->GetAllocation();
			//std::cout << rect.width << " " << std::endl;

			m_desktop.Update(0.f);
			render_window.clear();
			m_sfgui.Display(render_window);
			render_window.display();
		}
	}

	void NpcvGUI::OnCreateWindowClick() {
		++m_count;

		// Create a new window.
		auto window = sfg::Window::Create();

		std::stringstream sstr;
		sstr << "A new window (" << m_count << ")";
		window->SetTitle(sstr.str());

		// Widgets.
		auto destroy_button = sfg::Button::Create("Destroy");
		auto front_button = sfg::Button::Create("Main window to front");

		// Layout.
		auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
		box->Pack(sfg::Label::Create("This is a newly created window, from runtime, interactively."), false);
		box->Pack(sfg::Label::Create("You can move me around, try it!"), false);
		box->Pack(sfg::Label::Create("Or click the button below to destroy me. :-("), false);
		box->Pack(destroy_button, false);
		box->Pack(front_button, false);



		auto npcvImageBox = new ImageBox();
		npcv::utils::ImageStreamSTB tb;
		
		std::string lenaInput = getResourceManager()->getAbs("/input/lena.jpg");
		auto npImage = tb.Load(lenaInput.c_str());
		npcvImageBox->init();
		npcvImageBox->load(npImage);
		
		window->Add(npcvImageBox->sgMainBox);
		//window->Add(box);
		m_desktop.Add(window);

		// Signals.
		box->GetSignal(sfg::Window::OnSizeAllocate).Connect(std::bind(&NpcvGUI::_onResize, this));
		
		destroy_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&NpcvGUI::OnDestroyWindowClick, this));
		front_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&NpcvGUI::OnFrontClick, this));
	}

	void NpcvGUI::OnDestroyWindowClick() {
		// Obtain parent window.
		auto widget = sfg::Context::Get().GetActiveWidget();

		while (widget->GetName() != "Window") {
			widget = widget->GetParent();
		}

		// Remove window from desktop.
		m_desktop.Remove(widget);
	}

	void NpcvGUI::OnFrontClick() {
		m_desktop.BringToFront(m_window);
	}


	void NpcvGUI::setResourceManager(npcv::ResourceManager * manager)
	{
		_resManager = manager;
	}

	npcv::ResourceManager* NpcvGUI::getResourceManager()
	{
		if (_resManager == 0) {
			std::cerr << "npcvGui:NpcvGUI:getResourceManager: not set" << std::endl;
			return 0;
		}
		return _resManager;
	}


}


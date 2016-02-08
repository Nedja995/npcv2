#pragma once
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <sstream>

namespace npcvGui {
	class NpcvGUI
	{
	public:
		NpcvGUI();
		~NpcvGUI();

		void Run();

	private:
		static const unsigned int SCREEN_WIDTH;
		static const unsigned int SCREEN_HEIGHT;

		void OnCreateWindowClick();
		void OnDestroyWindowClick();
		void OnFrontClick();
		// Create an SFGUI. This is required before doing anything with SFGUI.
		sfg::SFGUI m_sfgui;

		sfg::Desktop m_desktop;
		sfg::Window::Ptr m_window;
		unsigned int m_count;
	};


}
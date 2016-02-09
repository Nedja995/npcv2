#pragma once
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <sstream>

#include <npcv/Application.h>
#include <npcv/utils/ResourceManager.h>

namespace npcvGui {

	class NpcvGUI
	{
	public:

		NpcvGUI();
		~NpcvGUI();

		void Run();

		static const unsigned int SCREEN_WIDTH;
		static const unsigned int SCREEN_HEIGHT;


		void setResourceManager(npcv::ResourceManager* manager);
		npcv::ResourceManager* getResourceManager();

	protected:
		npcv::ResourceManager* _resManager;

		void OnCreateWindowClick();
		void OnDestroyWindowClick();
		void OnFrontClick();
		void _onResize();
		// Create an SFGUI. This is required before doing anything with SFGUI.
		sfg::SFGUI m_sfgui;

		sfg::Desktop m_desktop;
		sfg::Window::Ptr m_window;
		unsigned int m_count;

	};


}
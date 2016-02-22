#include "npcv/ui/DialogFileSelectWindows.h"
#include "npcv/Config.h"
#ifdef _WIN64
#include <Windows.h>
#include <tchar.h>
#endif
#include <iostream>
namespace npcv {
	namespace ui {


		DialogFileSelectWindows::DialogFileSelectWindows()
			: _title(std::string("File Select"))
			, _multiselect(false)
			, _rootPath(std::string("fdsf"))
	//		, _pathsSelected(nullptr)
		{
			_pathSelected = new char[MAX_STR_PATH];
		}

		DialogFileSelectWindows::~DialogFileSelectWindows()
		{
		}

		void DialogFileSelectWindows::setTitle(std::string& title)
		{
			_title = title;
		}

		void DialogFileSelectWindows::setRoot(std::string & root)
		{
			_rootPath = root;
		}

		void DialogFileSelectWindows::show()
		{
			//MessageBox(0, "Hello World!", "Greetings", 0);
#ifdef _WIN64
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = 0;
			ofn.lpstrDefExt = 0;
			ofn.lpstrFile = this->_pathSelected;
			ofn.lpstrFile[0] = '\\0';
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFilter = 0;
			ofn.nFilterIndex = 0;
			ofn.lpstrInitialDir = 0;
			ofn.lpstrTitle = _T(_title.c_str());
			ofn.Flags = 0;

			GetOpenFileName(&ofn);
#endif

			if (_pathSelected == 0) {
				std::cerr << "npcv:ui:DialogFileSelectWindows:show: nothing selected" << std::endl;
			}

		}

		std::string * DialogFileSelectWindows::getPathSelected()
		{
			return new std::string(_pathSelected);
		}

		std::string * DialogFileSelectWindows::getPathsSelected()
		{
			return nullptr;
		}

		void DialogFileSelectWindows::setMultiselect(bool multiselect)
		{
			_multiselect = multiselect;
		}

	}
}
#include "npcv/Toolset.h"
#include "npcv/LogListenerDebug.h"
#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/abs/IImageStream.h"
#include <stdarg.h>

#if _WIN32
#include "npcv/ui/DialogFileSelectWindows.h"
#endif

namespace npcv {

	using namespace utils;

	Toolset* Toolset::_sharedInstance = 0;

	Toolset& Toolset::SharedInstance()
	{
		if (Toolset::_sharedInstance == 0) {
			Toolset::_sharedInstance = new Toolset();
		}
		return *_sharedInstance;
	}

	Toolset::Toolset() 
		: log(*new LogListenerDebug())
		, imageStream(*((IImageStream*)new ImageStreamSTB()))
	{

	}

	Toolset::~Toolset()
	{
		delete &log;
	}

	ui::IDialogFileSelect& Toolset::uiDialogFileselect()
	{
#if _WIN32
		return *new ui::DialogFileSelectWindows();
#elif __linux__

#endif

		return *new ui::DialogFileSelectWindows();
	}


}
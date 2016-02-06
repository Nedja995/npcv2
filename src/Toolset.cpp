#include "npcv/Toolset.h"
#include "npcv/LogListenerDebug.h"
#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/abs/IImageStream.h"
#include <stdarg.h>

namespace npcv {

	using namespace utils;

	Toolset* Toolset::_sharedInstance = 0;

	Toolset * Toolset::SharedInstance()
	{
		if (Toolset::_sharedInstance == 0) {
			Toolset::_sharedInstance = new Toolset();
		}
		return _sharedInstance;
	}

	Toolset::Toolset()
	{
		log = new LogListenerDebug();
		imageStream = (npcv::IImageSteam*)new ImageStreamSTB();
	}

	Toolset::~Toolset()
	{
		delete log;
	}


}
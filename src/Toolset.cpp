#include "npcv/Toolset.h"

#include "npcv/LogListenerDebug.h"

namespace npcv {

	Toolset * Toolset::SharedInstance()
	{
		if (_sharedInstance == 0) {
			_sharedInstance = new Toolset();
		}
		return _sharedInstance;
	}

	Toolset::Toolset()
	{
		Log = new LogListenerDebug();
	}

	Toolset::~Toolset()
	{
		delete Log;
	}
	void DebugLog(const char * message)
	{
		//Toolset::SharedInstance()->Log->Write(message);
	}
}
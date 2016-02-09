#ifndef __NPCV_TOOLSET__
#define __NPCV_TOOLSET__

#include "npcv/abs/ILogListener.h"
#include "npcv/abs/IImageStream.h"

namespace npcv {

	//void DebugLog(const char* message);

	class Toolset {
	public:
		static Toolset* SharedInstance();

		Toolset();
		~Toolset();

		ILogListener* log;
		IImageSteam* imageStream;


	private:
		static Toolset* _sharedInstance;
	};

}
#endif
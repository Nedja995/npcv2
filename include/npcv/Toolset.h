#ifndef __NPCV_TOOLSET__
#define __NPCV_TOOLSET__

#include "abs/LogListener.h"

namespace npcv {

	//void DebugLog(const char* message);

	class Toolset {
	public:
		static Toolset* SharedInstance();

		Toolset();
		~Toolset();

		LogListener* Log;

	private:
		static Toolset* _sharedInstance;
	};

}
#endif
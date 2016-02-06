#ifndef _INTERFACE_FILEPATH__
#define _INTERFACE_FILEPATH__

namespace npcv {

	class IFilePath {
	public:	
		virtual char* GetPath(const char* path) = 0;
	};

}

#endif
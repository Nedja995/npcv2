#ifndef _ABS_FILEPATH__
#define _ABS_FILEPATH__

namespace npcv {

	class AbsFilePath {
	public:
		virtual char* GetPath(const char* path) = 0;
	};

}

#endif
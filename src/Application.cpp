#include "npcv/Application.h"

namespace npcv {

	Application::Platform Application::getRuntimePLatform()
	{
#ifdef _WIN32
		return Platform::Windows;
#elif __unix__
		return Platform::Unix;
#endif
		return Platform::Windows;
	}
}

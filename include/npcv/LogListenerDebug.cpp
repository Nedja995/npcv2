#include "LogListenerDebug.h"

#include <iostream>

namespace npcv {

	using namespace std;

	void LogListenerDebug::Write(const char * message)
	{
		cout << message << endl;
	}

	char ** LogListenerDebug::GetMessages()
	{
		return nullptr;
	}
}
#include "npcv/LogListenerDebug.h"

#include<string.h>
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

	/*ostream &DebugStreamBuffer::operator<<(ostream &output,
		const char& D)
	{
		output << "LOGGG:: " << D;
		std::cout << "LOGG: " << D;
		return output;
	}*/
	

	DebugStream::DebugStream()

	{
	}

}
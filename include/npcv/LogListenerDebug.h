#ifndef __LOGLISTENER_DEBUG__
#define __LOGLISTENER_DEBUG__
#include "npcv/abs/ILogListener.h"
#include <iostream>
#include <streambuf>
#include <locale>
#include <cstdio>
namespace npcv {
	using namespace std;
	class LogListenerDebug : public ILogListener {
		// Inherited via ILogListener
		virtual void Write(const char * message) override;
		virtual char ** GetMessages() override;
	}; 
	
	class DebugStream
	{
	public:
		DebugStream();
		/*ostream operator>>(ostream &output,
			const char& D);*/
		
	};

	//extern class DebugStream;
	template <typename T>
	DebugStream& operator<< (DebugStream &s, const T &x)
	 {
		//format x as you please
		std::cout << "DebugStream: " << x;
		return s;
	}

	//struct MyCout {};

	//extern MyCout myCout;

}
#endif

#ifndef _INTERFACE_LOG_LISTENER__
#define _INTERFACE_LOG_LISTENER__

#include <istream>

namespace npcv {

	class ILogListener {
	public:
		virtual ~ILogListener() {};

		virtual void Write(const char* message) = 0;
		
		virtual char** GetMessages() = 0;
	};

	//extern class ILogListener;
	template <typename T>
	ILogListener& operator<< (ILogListener &s, const T &x)
	{
		//format x as you please
		//std::string st("HA");
		//st << "ILogListener: " << x;
		return s;
	}
}

#endif

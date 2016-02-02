#ifndef _ABS_LOG_LISTENER__
#define _ABS_LOG_LISTENER__

namespace npcv {

	class LogListener {
	public:
		virtual ~LogListener() {};

		virtual void Write(const char* message) = 0;
		
		virtual char** GetMessages() = 0;
	};

}

#endif
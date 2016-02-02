#ifndef __LOGLISTENER_DEBUG__
#define __LOGLISTENER_DEBUG__
#include "npcv/abs/LogListener.h"
namespace npcv {

	class LogListenerDebug : public LogListener {
		// Inherited via LogListener
		virtual void Write(const char * message) override;
		virtual char ** GetMessages() override;
	};

}
#endif
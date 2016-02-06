#ifndef _INTERFACE_PROCESS__
#define _INTERFACE_PROCESS__

namespace npcv {

	class IProcess {

	public:

		virtual ~IProcess() = 0  {};

		virtual void initialize() = 0;

		virtual void execute() = 0;

		virtual void free() = 0;

		virtual bool isInitialized() = 0;

		virtual bool isProcessing() = 0;

	};
}

#endif
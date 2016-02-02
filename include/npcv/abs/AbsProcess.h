#ifndef _ABS_PROCESS__
#define _ABS_PROCESS__

namespace npcv {

	class AbsProcess {

	public:
		AbsProcess();
		virtual ~AbsProcess() = 0;

		virtual void Initialize() = 0;

		virtual void Execute() = 0;

		virtual void Free() = 0;

	};
}

#endif
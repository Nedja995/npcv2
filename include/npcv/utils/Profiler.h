#ifndef _NPCV_PROFILER__
#define _NPCV_PROFILER__
#include <iostream>
#include <chrono>

namespace npcv {
	namespace debug {


		template<typename TimeT = std::chrono::milliseconds>
		class Profiler
		{
		public:
			template<typename F, typename ...Args>
			static typename TimeT::rep execution(F&& func, Args&&... args);

		};

	}
}




#endif
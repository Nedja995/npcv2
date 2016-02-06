#include "..\..\include\npcv\utils\Profiler.h"

namespace npcv { namespace debug {

	template<typename TimeT>
	template<typename F, typename ...Args>
	inline typename TimeT::rep debug::Profiler<TimeT>::execution(F && func, Args && ...args)
	{
		auto start = std::chrono::system_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
			(std::chrono::system_clock::now() - start);
		return duration.count();
	}

}
}
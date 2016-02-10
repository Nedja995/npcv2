#pragma once
#include <SFGUI/Window.hpp>
namespace npcvGui {

	class WinMatrixFilter : public sfg::Window {
	public:
		typedef std::shared_ptr<WinMatrixFilter> Ptr; //!< Shared pointer.
		typedef std::shared_ptr<const WinMatrixFilter> PtrConst; //!< Shared pointer.

		static Ptr Create();

	};


}
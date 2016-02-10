#pragma once

#include <string>

namespace npcv {
	namespace ui {

		class IDialogFileSelect {
		public:
			virtual void setTitle(std::string& title) = 0;
			virtual void setRoot(std::string& root) = 0;
			virtual void setMultiselect(bool multiselect) = 0;
			virtual void show() = 0;
			virtual std::string * getPathSelected() = 0;
			virtual std::string* getPathsSelected() = 0;

		};

	}
}
#pragma once

#include "../abs/IDialogFileSelect.h"
#include <string>

namespace npcv {
	namespace ui {

		class DialogFileSelectWindows : public IDialogFileSelect {
		public:
			DialogFileSelectWindows();
			~DialogFileSelectWindows();
			// Inherited via IDialogFileSelect
			virtual void setTitle(std::string& title) override;

			virtual void setRoot(std::string & root) override;

			virtual void setMultiselect(bool multiselect) override;

			virtual void show() override;

			virtual std::string * getPathSelected() override;

			virtual std::string * getPathsSelected() override;

		protected:
			std::string& _title;
			bool _multiselect;
			std::string& _rootPath;
			char* _pathSelected;
			//char* _pathsSelected[];

		};
	}
}
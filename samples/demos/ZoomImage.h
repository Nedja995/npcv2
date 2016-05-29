#pragma once
#include "npcv/abs/IDemoConsole.h"

namespace npcv {
	namespace demos {
		class ZoomImage : public abs::IDemoConsole {
		public:
			ZoomImage(int argc, char* argv[]);



			// Inherited via IDemoConsole
			virtual void help() override;


			// Inherited via IDemoConsole
			virtual bool run() override;

		protected:
			// Inherited via IDemoConsole
			virtual bool _parse(int argc, char * argv[]) override;
		};
	}
}
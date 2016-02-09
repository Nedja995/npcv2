#pragma once



namespace npcv {

	class Application {
	public:
		static enum Platform {
			Windows = 0,
			Unix = 1,
			Android = 2
		};


		static Platform getRuntimePLatform();

	};



}

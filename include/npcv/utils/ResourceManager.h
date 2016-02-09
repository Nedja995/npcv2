#pragma once
#include <string>
namespace npcv {

	class ResourceManager {
	public:
		ResourceManager();
		ResourceManager(std::string& rootDirectory);
		~ResourceManager();

		std::string getAbs(const char* relativeFilepath);
		
		std::string getRootDirPath();
		void setRootDirPath(std::string& rootDirectory);

		static void convertPathToPlatform(std::string path);

	protected:
		std::string rootDirectory;

	};

}
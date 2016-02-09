#include "npcv/utils/ResourceManager.h"
#include "npcv/Application.h"
#include <string>
namespace npcv {

	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::ResourceManager(std::string & rootDirectory)
	{
		convertPathToPlatform(rootDirectory);
		this->rootDirectory = rootDirectory;
	}

	ResourceManager::~ResourceManager()
	{
	}

	std::string ResourceManager::getAbs(const char* relativeFilepath)
	{
		std::string ret = rootDirectory + relativeFilepath;
		convertPathToPlatform(ret);
		return ret;
	}

	std::string ResourceManager::getRootDirPath()
	{
		return rootDirectory;
	}

	void ResourceManager::setRootDirPath(std::string & rootDirectory)
	{
		this->rootDirectory = rootDirectory;
	}

	void ResourceManager::convertPathToPlatform(std::string path)
	{
		Application::Platform platform = Application::getRuntimePLatform();
		if (platform == Application::Platform::Windows) {
			for (int i = 0; i < path.length(); ++i) {
				if (path[i] == '/')
					path[i] = '\\';
			}
		}
	}

}
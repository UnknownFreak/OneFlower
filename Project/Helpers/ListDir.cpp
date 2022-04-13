#include "ListDir.hpp"

#include <filesystem>
#include <Module/EngineModuleManager.hpp>

namespace Helpers::os
{
	std::vector<Core::String> listDirectory(const Core::String& path, const Core::String& ext, const bool& removeExtInReturn)
	{
		std::vector<Core::String> l;
		for (auto& p : std::filesystem::directory_iterator(path))
		{
			if (p.path().extension() == ext)
				if (removeExtInReturn)
					l.push_back(Engine::GetModule<Core::StringConverter>().toUtf8(p.path().stem().c_str()));
				else
					l.push_back(Engine::GetModule<Core::StringConverter>().toUtf8(p.path().filename().c_str()));
		}
		return l;
	}

#ifdef _UNITTESTS_

	void clearDirectory(const Core::String& path)
	{
		std::filesystem::remove_all(path);
		std::filesystem::create_directory(path);
	}

#endif
}

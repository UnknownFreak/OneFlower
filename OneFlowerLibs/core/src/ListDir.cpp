#include <os/ListDir.hpp>

#include <filesystem>

namespace OneFlower::os
{
	std::vector<Core::String> listDirectory(const Core::String& path, const Core::String& ext, const bool& removeExtInReturn)
	{
		std::vector<Core::String> l;
		for (auto& p : std::filesystem::directory_iterator(path))
		{
			if (p.path().extension() == ext)
				if (removeExtInReturn)
				{
					auto x = p.path().stem().generic_u8string();
					l.push_back(Core::String(x.begin(), x.end()));
				}
				else
				{
					auto x = p.path().filename().generic_u8string();
					l.push_back(Core::String(x.begin(), x.end()));
				}
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

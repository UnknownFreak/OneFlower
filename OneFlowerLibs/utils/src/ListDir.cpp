#include <os/ListDir.hpp>

#include <filesystem>

namespace of::os
{
	std::vector<common::String> listDirectory(const common::String& path, const common::String& ext, const bool& removeExtInReturn)
	{
		std::vector<common::String> l;
		for (auto& p : std::filesystem::directory_iterator(path))
		{
			if (p.path().extension() == ext)
				if (removeExtInReturn)
				{
					auto x = p.path().stem().generic_u8string();
					l.push_back(common::String(x.begin(), x.end()));
				}
				else
				{
					auto x = p.path().filename().generic_u8string();
					l.push_back(common::String(x.begin(), x.end()));
				}
		}
		return l;
	}

#ifdef _UNITTESTS_

	void clearDirectory(const common::String& path)
	{
		std::filesystem::remove_all(path);
		std::filesystem::create_directory(path);
	}

#endif
}

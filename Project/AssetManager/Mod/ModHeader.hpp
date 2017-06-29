#ifndef MODHEADER_HPP
#define	MODHEADER_HPP

#include <vector>
#include <Core\String.hpp>
#include "../Version/Version.hpp"
#include <Logger\Logger.hpp>
class ModHeader
{
	// This is changed when anything is added or removed
	OneVersion fileVersion = OneVersion(1, 0, 1);

public:

	Core::String name = "OneFlower.main";
	std::vector<Core::String> dependencies;

	OneVersion ver = OneVersion(1,0,0);

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(fileVersion);
		
		ar(name);
		if (fileVersion >= OneVersion(1, 0, 1))
			ar(ver);
		ar(dependencies.size());
		for each (Core::String var in dependencies)
		{
			ar(var);
		}
	}

	template<class Archive>
	void load(Archive& ar)
	{
		OneVersion myVersion = OneVersion(1,0,0);
		ar(myVersion);

		dependencies.clear();
		size_t mysize;
		std::string mydep;
		ar(name);
		if (myVersion >= OneVersion(1, 0, 1))
		{
			ar(ver);
			Logger::Info("Mod [" + name + "] version is: " + ver.c_str());
		}
		else
			Logger::Info("Current header version does not support loading mod file version (Save file again to apply this feature)");
		ar(mysize);
		for (size_t i = 0; i < mysize; i++)
		{
			ar(mydep);
			dependencies.push_back(mydep);
		}
	}
};

#endif
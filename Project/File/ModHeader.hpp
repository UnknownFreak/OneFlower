#ifndef MODHEADER_HPP
#define	MODHEADER_HPP

#include <vector>

#include <Helpers\String.hpp>
#include <Module/Logger/OneLogger.hpp>
#include <Helpers\Version.hpp>

class ModHeader
{
	OneVersion modFileVersion = OneVersion::getCurrentVersion();

public:

	Core::String name = "";
	std::vector<Core::String> dependencies;

	OneVersion modVersion = OneVersion(1, 0, 0);

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(modFileVersion);
		ar(name);
		if (modFileVersion >= OneVersion(1, 0, 1))
			ar(modVersion);
		ar(dependencies.size());
		for(Core::String var : dependencies)
		{
			ar(var);
		}
	}

	template<class Archive>
	void load(Archive& ar)
	{
		OneVersion myVersion;
		ar(myVersion);

		dependencies.clear();
		size_t mysize;
		std::string mydep;
		ar(name);
		if (myVersion >= OneVersion(1, 0, 1))
		{
			ar(modVersion);
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("ModHeader").Info("Mod [" + name + "] version is: " + modVersion.str());
		}
		else
			Engine::GetModule<EngineModule::Logger::OneLogger>().getLogger("ModHeader").Info("Current header version does not support loading mod file version (Save file again to apply this feature)");
		ar(mysize);
		for (size_t i = 0; i < mysize; i++)
		{
			ar(mydep);
			dependencies.push_back(mydep);
		}
	}
};

#endif
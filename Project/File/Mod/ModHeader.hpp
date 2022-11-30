#ifndef MODHEADER_HPP
#define	MODHEADER_HPP

#include <vector>

#include <utils/common/string.hpp>
#include <Module/ModuleManager.hpp>

#include <Module/Logger/OneLogger.hpp>
#include <utils/common/version.hpp>

namespace File::Mod
{

	class Header
	{
		OneVersion modFileVersion = OneVersion::getCurrentVersion();

	public:

		of::common::String name = "";
		std::vector<of::common::String> dependencies;

		OneVersion modVersion = OneVersion(1, 0, 0);

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(modFileVersion);
			ar(name);
			if (modFileVersion >= OneVersion(1, 0, 1))
				ar(modVersion);
			ar(dependencies.size());
			for (of::common::String var : dependencies)
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
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("File::Mod::ModHeader").Info("Mod [" + name + "] version is: " + modVersion.str());
			}
			else
				of::engine::GetModule<of::module::logger::OneLogger>().getLogger("File::Mod::ModHeader").Info("Current header version does not support loading mod file version (Save file again to apply this feature)");
			ar(mysize);
			for (size_t i = 0; i < mysize; i++)
			{
				ar(mydep);
				dependencies.push_back(mydep);
			}
		}
	};
};

#endif
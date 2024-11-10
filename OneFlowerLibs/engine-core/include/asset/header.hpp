#pragma once

#include <vector>

#include <utils/common/string.hpp>
#include <utils/common/version.hpp>
#include <logger/Logger.hpp>

namespace of::asset
{

	class Header
	{
		OneVersion modFileVersion = OneVersion::getCurrentVersion();
		of::common::String header;
		bool valid = true;
	public:

		inline bool isValid() const { return valid; }

		of::common::String name = "";
		std::vector<of::common::String> dependencies;

		OneVersion modVersion = OneVersion(1, 0, 0);

		template <class Archive>
		void save(Archive& ar) const
		{
			ar("ofHDR");
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
			ar(header);
			if (header != "ofHDR")
			{
				logger::get().Error("Invalid file header");
				valid = false;
				return;
			}
			OneVersion myVersion;
			ar(myVersion);

			dependencies.clear();
			size_t mysize;
			std::string mydep;
			ar(name);
			if (myVersion >= OneVersion(1, 0, 1))
			{
				ar(modVersion);
				of::logger::get().getLogger("File::Header").Info("Header [" + name + "] version is: " + modVersion.str());
			}
			else
				of::logger::get().getLogger("File::Header").Info("Current header version does not support loading header file version (Save file again to apply this feature)");
			ar(mysize);
			for (size_t i = 0; i < mysize; i++)
			{
				ar(mydep);
				dependencies.push_back(mydep);
			}
		}
	};
};

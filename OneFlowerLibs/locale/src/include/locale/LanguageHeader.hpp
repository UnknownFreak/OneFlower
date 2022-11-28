#ifndef LanguageHeader_HPP
#define LanguageHeader_HPP 
#include <utils/common/String.hpp>
#include <utils/common/uuid.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

#include <map>
#include <vector>

namespace of::locale
{
	struct LanguageHeader
	{
		LanguageHeader() = default;
		typedef common::String LanguageName;
		std::map<LanguageName, std::vector<common::uuid>> addedIds;
		std::map<LanguageName, std::vector<common::uuid>> moddedIds;

		template<class Archive>
		void load(Archive& ar)
		{
			ar(addedIds);
			ar(moddedIds);
		}
		template<class Archive>
		void save(Archive& ar) const
		{
			ar(addedIds);
			ar(moddedIds);
		}
	};
}

#endif 

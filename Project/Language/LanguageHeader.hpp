#ifndef LanguageHeader_HPP
#define LanguageHeader_HPP 
#include <utils/common/string.hpp>
#include <utils/common/uuid.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

#include <map>
#include <vector>

namespace Language
{
	struct LanguageHeader
	{
		LanguageHeader() = default;
		typedef of::common::String LanguageName;
		std::map<LanguageName, std::vector<of::common::uuid>> addedIds;
		std::map<LanguageName, std::vector<of::common::uuid>> moddedIds;

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

#ifndef LanguageHeader_HPP
#define LanguageHeader_HPP 
#include <Helpers/String.hpp>
#include <Helpers/uuid.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

#include <map>
#include <vector>

namespace Language
{
	struct LanguageHeader
	{
		LanguageHeader() = default;
		typedef Core::String LanguageName;
		std::map<LanguageName, std::vector<Core::uuid>> addedIds;
		std::map<LanguageName, std::vector<Core::uuid>> moddedIds;

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

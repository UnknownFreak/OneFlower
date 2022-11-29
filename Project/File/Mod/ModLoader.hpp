#ifndef MODLOADER_HPP
#define MODLOADER_HPP
#include <map>
#include <utils/common/string.hpp>

#include <Interfaces/IEngineModule.hpp>

namespace File::Mod
{

	class Loader : public Interfaces::IEngineResource<Loader>
	{

	public:
		Loader() = default;
		std::map <of::common::String, size_t> loadOrder;

		const size_t getModPosition(const of::common::String& mod) const;

		template <class Archive>
		void load(Archive& ar)
		{
			std::string tmp;
			size_t size;
			ar(size);
			for (size_t i = 0; i < size; i++)
			{
				ar(tmp);
				loadOrder.insert(std::pair<of::common::String, size_t>(tmp, i));
			}
		}
		template <class Archive>
		void save(Archive& ar) const
		{
			size_t size = loadOrder.size();
			ar(size);
			std::map<of::common::String, size_t>::const_iterator it = loadOrder.begin();
			std::map<of::common::String, size_t>::const_iterator eit = loadOrder.end();

			for (it; it != eit; it++)
			{
				ar(it->first);
				ar(it->second);
			}
		}

		Enums::EngineResourceType& getType() const
		{
			return type;
		}
	};
};
#endif 
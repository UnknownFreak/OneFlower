#ifndef LOADER_HPP
#define LOADER_HPP
#include <map>

#include <utils/common/String.hpp>
#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

namespace of::file
{

	class Loader : public of::module::interface::IEngineResource<Loader>
	{

	public:
		Loader() = default;
		std::map <common::String, size_t> loadOrder;

		const size_t getModPosition(const common::String& mod) const;

		template <class Archive>
		void load(Archive& ar)
		{
			std::string tmp;
			size_t size;
			ar(size);
			for (size_t i = 0; i < size; i++)
			{
				ar(tmp);
				loadOrder.insert(std::pair<common::String, size_t>(tmp, i));
			}
		}
		template <class Archive>
		void save(Archive& ar) const
		{
			size_t size = loadOrder.size();
			ar(size);
			std::map<common::String, size_t>::const_iterator it = loadOrder.begin();
			std::map<common::String, size_t>::const_iterator eit = loadOrder.end();

			for (it; it != eit; it++)
			{
				ar(it->first);
				ar(it->second);
			}
		}

		module::EngineResourceType& getType() const;
	};
};
#endif 
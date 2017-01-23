#ifndef MODLOADER_HPP
#define MODLOADER_HPP
#include <map>
#include <string>
class ModLoader
{
public:
	ModLoader() = default;
	std::map <std::string, size_t> loadOrder;

	size_t getModPosition(std::string mod);

	template <class Archive>
	void load(Archive& ar)
	{
		std::string tmp;
		size_t size;
		ar(size);
		for (size_t i = 0; i < size; i++)
		{
			ar(tmp);
			loadOrder.insert(std::pair<std::string, size_t>(tmp, i));
		}
	}
	template <class Archive>
	void save(Archive& ar) const
	{
		size_t size = loadOrder.size();
		ar(size);
		std::map<std::string, size_t>::const_iterator it = loadOrder.begin();
		std::map<std::string, size_t>::const_iterator eit = loadOrder.end();

		for (it; it != eit; it++ )
		{
			ar(it->first);
			ar(it->second);
		}
	}
};
#endif 
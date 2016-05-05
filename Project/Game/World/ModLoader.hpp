#ifndef MODLOADER_HPP
#define MODLOADER_HPP
#include <map>
class ModLoader
{
public:
	ModLoader() = default;
	std::map <std::string, size_t> loadOrder;

	size_t getModPosition(std::string mod);
protected:
	template <class Archive>
	friend void load(Archive& ar, ModLoader& mod);
};
#endif 
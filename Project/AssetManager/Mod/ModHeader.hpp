#ifndef MODHEADER_HPP
#define	MODHEADER_HPP

#include <vector>
#include <Core\String.hpp>
class ModHeader
{
public:

	Core::String name = "OneFlower.main";
	std::vector<Core::String> dependencies;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(name);
		ar(dependencies.size());
		for each (Core::String var in dependencies)
		{
			ar(var);
		}
	}
	template<class Archive>
	void load(Archive& ar)
	{
		size_t mysize;
		ar(name);
		ar(mysize);
		for (size_t i = 0; i < mysize; i++)
		{
			std::string mydep;
			ar(mydep);
			dependencies.push_back(mydep);
		}
	}
};

#endif
#ifndef MODHEADER_HPP
#define	MODHEADER_HPP

#include <vector>

class ModHeader
{
public:

	std::string name = "OneFlower.main";
	std::vector<std::string> dependencies;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(name);
		ar(dependencies.size());
		for each (std::string var in dependencies)
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
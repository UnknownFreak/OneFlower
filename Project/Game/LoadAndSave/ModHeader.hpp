#ifndef MODHEADER_HPP
#define	MODHEADER_HPP

#include <vector>

class ModHeader
{

public:

	std::string name = "OneFlower.main";
	std::vector<std::string> dependencies;

protected:

	template<class Archive>
	friend void save(Archive &ar, const ModHeader& mh);
	template<class Archive>
	friend void load(Archive &ar, ModHeader & mh);


};


#endif
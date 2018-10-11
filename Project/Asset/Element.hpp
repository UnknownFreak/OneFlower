#ifndef Element_HPP
#define Element_HPP

#include <map>

#include "IObject.hpp"
#include "IRequestable.hpp"

class Element : public IRequestable, public IObject
{

public:

	double damageToUnknownType = 0.0;

	std::map<std::pair<Core::String, size_t>, double> elementAttributes;

	Element();
	Element(Core::String elementName);
	Element(const Element& copy);

	double getElementModifier();
	double getElementModifier(Core::String name, size_t ID);

	template<class Archive>
	void load(Archive& ar)
	{
		ar(cereal::base_class<IObject>(this));
		ar(cereal::base_class<IRequestable>(this));
		ar(elementAttributes);
		ar(damageToUnknownType);
	}
	template<class Archive>
	void save(Archive& ar) const
	{
		ar(cereal::base_class<IObject>(this));
		ar(cereal::base_class<IRequestable>(this));
		ar(elementAttributes);
		ar(damageToUnknownType);
	}

};


#endif
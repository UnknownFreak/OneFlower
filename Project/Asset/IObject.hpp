#ifndef IObject_HPP
#define IObject_HPP

#include <Core\String.hpp>
class IObject
{
public:
	
	Core::String name;
	Core::String tag;

	inline IObject(Core::String name) : name(name), tag()
	{}
	inline IObject() : IObject("")
	{}
	inline IObject(const IObject& copy) : name(copy.name), tag(copy.tag)
	{}
	inline IObject& operator=(const IObject& right)
	{
		name = right.name;
		tag = right.tag;
		return *this;
	}

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(name, tag);
	}
	template <class Archive>
	void load(Archive& ar)
	{
		ar(name, tag);
	}
};


#endif
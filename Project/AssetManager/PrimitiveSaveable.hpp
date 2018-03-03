#ifndef PrimitiveSaveable_HPP
#define PrimitiveSaveable_HPP

#include "IRequestable.hpp"
#include <cereal\types\vector.hpp>

template <class T>
class PrimitiveSaveable : public IRequestable
{

public:
	T value;
	Core::String name;

	inline PrimitiveSaveable() : IRequestable("", 0, OneVersion(1, 0, 0)), value(), name()
	{
	}

	inline PrimitiveSaveable(T value, Core::String name) : IRequestable("", 0, OneVersion(1, 0, 0)), value(value), name(name)
	{
	}

	inline PrimitiveSaveable(T value, Core::String name, const Core::String fromMod, const size_t ID, const OneVersion version) : IRequestable(fromMod, ID, version), value(value), name(name)
	{
	}

	inline PrimitiveSaveable(const PrimitiveSaveable& copy) : IRequestable(copy), value(copy.value), name(copy.name)
	{
	}

	inline Core::String getName() const override
	{
		return name;
	}

	inline Core::String getValue() const override
	{
		return "";
	}


	inline PrimitiveSaveable& operator=(const PrimitiveSaveable& right)
	{
		value = right.value;
		name = right.name;
		fromMod = right.fromMod;
		ID = right.ID;
		mode = right.mode;
		objectVersion = right.objectVersion;
		return *this;
	}

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(value);
		ar(name);
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(cereal::base_class<IRequestable>(this));
		ar(value);
		ar(name);
	}
};
#endif
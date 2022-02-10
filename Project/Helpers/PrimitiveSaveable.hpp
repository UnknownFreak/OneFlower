#ifndef PrimitiveSaveable_HPP
#define PrimitiveSaveable_HPP

#include <Interfaces/IRequestable.hpp>
#include <Interfaces/IObject.hpp>
#include <cereal\types\vector.hpp>

template <class T>
class PrimitiveSaveable : public Interfaces::IRequestable, public Interfaces::IObject
{
	template <class In = T>
	inline typename std::enable_if<std::is_same<std::vector<Core::String>, In>::value, 
	Core::String>::type str() const
	{
		return "<List Data>";
	}

	template <class In = T>
	inline typename std::enable_if<!std::is_same<std::vector<Core::String>, In>::value,
	Core::String>::type str() const
	{
		return Core::toString(value);
	}

public:
	T value;

	inline PrimitiveSaveable() : PrimitiveSaveable(T(), "")
	{
	}

	inline PrimitiveSaveable(T value, Core::String name) : PrimitiveSaveable(value, name, "", Core::uuid::nil(), OneVersion::EMPTY)
	{
	}

	inline PrimitiveSaveable(T value, Core::String name, const Core::String fromMod, const Core::uuid ID, const OneVersion version) : IRequestable(fromMod, ID, version), IObject(name), value(value)
	{
	}

	inline PrimitiveSaveable(const PrimitiveSaveable& copy) : IRequestable(copy), IObject(copy), value(copy.value)
	{
	}

	inline Core::String getName() const override
	{
		return name;
	}

	inline Core::String getValue() const override
	{
		return str();
	}

	inline PrimitiveSaveable& operator=(const PrimitiveSaveable& right)
	{
		value = right.value;
		name = right.name;
		tag = right.tag;
		fromMod = right.fromMod;
		ID = right.ID;
		mode = right.mode;
		objectVersion = right.objectVersion;
		return *this;
	}

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(fromMod, ID, mode, objectVersion);
		ar(cereal::base_class<IObject>(this));
		ar(value);
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(fromMod, ID, mode, objectVersion);
		ar(cereal::base_class<IObject>(this));
		ar(value);
	}

	// Inherited via IRequestable
	virtual Interfaces::TypeInfo getTrait() const override
	{
		return { Interfaces::Trait<PrimitiveSaveable<T>>::typeId };
	}
};
#endif
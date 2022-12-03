#ifndef PrimitiveSaveable_HPP
#define PrimitiveSaveable_HPP

#include <file/archive/Requestable.hpp>
#include <Interfaces/IObject.hpp>
#include <cereal\types\vector.hpp>

template <class T>
class PrimitiveSaveable : public of::file::archive::Requestable, public Interfaces::IObject
{
	template <class In = T>
	inline typename std::enable_if<std::is_same<std::vector<of::common::String>, In>::value,
		of::common::String>::type str() const
	{
		return "<List Data>";
	}

	template <class In = T>
	inline typename std::enable_if<!std::is_same<std::vector<of::common::String>, In>::value,
		of::common::String>::type str() const
	{
		return of::common::toString(value);
	}

public:
	T value;

	inline PrimitiveSaveable() : PrimitiveSaveable(T(), "")
	{
	}

	inline PrimitiveSaveable(T value, of::common::String name) : PrimitiveSaveable(value, name, "", of::common::uuid::nil(), OneVersion::EMPTY)
	{
	}

	inline PrimitiveSaveable(T value, of::common::String name, const of::common::String fromMod, const of::common::uuid ID, const OneVersion version) : Requestable(fromMod, ID, version), IObject(name), value(value)
	{
	}

	inline PrimitiveSaveable(const PrimitiveSaveable& copy) : Requestable(copy), IObject(copy), value(copy.value)
	{
	}

	inline of::common::String getName() const override
	{
		return name;
	}

	inline of::common::String getValue() const override
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
	virtual of::file::archive::TypeInfo getTrait() const override
	{
		return { of::file::archive::Trait<PrimitiveSaveable<T>>::typeId };
	}
};

CEREAL_REGISTER_TYPE(PrimitiveSaveable<of::common::String>);
CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, PrimitiveSaveable<of::common::String>);
#endif
#pragma once

#include <file/archive/Requestable.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>


class DataPacker
{
	of::common::String packed;
	std::stringstream ss;

	template<class T>
	void pack(const T& tType) {ss << tType};

	template<class T>
	T unpack() 
	{
		T tType;
		ss >> tType;
	};

	template<class Archive>
	void load(Archive& ar)
	{
		packed = ss.str();
		ar(packed);
	}
	template<class Archive>
	void save(Archive& ar) const
	{
		ar(packed);
		ss << packed;
	}

};

class TypeId
{
	// someidentifier
};

class ProxyBase
{
	static std::map<TypeId, std::function<std::shared_ptr<ProxyBase>(DataPacker&)>> constructionInstances;

public:

	static void registerDerivedType(const TypeId& ty, std::function < std::shared_ptr<ProxyBase>(DataPacker& )> fn) { constructionInstances[ty] = fn; }

	static std::shared_ptr<ProxyBase> construct(const TypeId& ty, DataPacker& p) {
		if (constructionInstances.find(ty) != constructionInstances.end())
		{
			return constructionInstances[ty](p);
		}
	}

	virtual TypeId getTypeId() = 0;

	virtual void pack(DataPacker& packer) = 0;

};

class Custom : public of::file::archive::Requestable
{

	DataPacker packer;

public:

	Custom() : of::file::archive::Requestable(of::file::ObjectType::Element) {};
	~Custom() {};

	std::shared_ptr<ProxyBase> a;

	template<class Archive>
	void load(Archive& ar)
	{
		ar(cereal::base_class<of::file::archive::Requestable>(this));

		TypeId ty;
		ar(ty);
		ar(packer);
		a = CustomProxyBase::construct(ty, packer);
		if (a.operator bool() == false)
		{
			this->mode = of::file::archive::ObjectSaveMode::REMOVE;
		}

	}
	template<class Archive>
	void save(Archive& ar) const
	{
		ar(cereal::base_class<of::file::archive::Requestable>(this));
		ar(a->getTypeId());
		a->pack(packer);
		ar(packer);

	}

	// Inherited via IRequestable
	virtual of::file::archive::TypeInfo getTrait() const override
	{
		return { of::file::archive::Trait<Custom>::typeId };
	}
	of::common::String getName() const override
	{
		return "name";
	}

};

of::common::uuid of::file::archive::Trait<Custom>::typeId = of::common::uuid("1423d23c-e7d0-493a-9e03-0c68a1714703");

//CEREAL_REGISTER_TYPE(Derived);

CEREAL_REGISTER_POLYMORPHIC_RELATION(of::file::archive::Requestable, Custom);
//CEREAL_REGISTER_POLYMORPHIC_RELATION(Custom, Derived);
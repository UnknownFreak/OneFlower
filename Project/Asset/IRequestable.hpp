#ifndef IREQUESTABLE_HPP
#define IREQUESTABLE_HPP
#include <Core/uuid.hpp>
#include <Core\String.hpp>
#include "ObjectSaveMode.hpp"
#include "Version.hpp"

struct IRequestable
{

	Core::String fromMod;
	Core::uuid ID;
	ObjectSaveMode mode = ObjectSaveMode::ADD;

	OneVersion objectVersion;


	inline IRequestable() : fromMod(""), ID(Core::uuid()), objectVersion(0, 0, 0) {}
	inline IRequestable(const Core::String fromMod, const Core::uuid ID, const OneVersion version) : fromMod(fromMod), ID(ID), objectVersion(version) {}
	inline IRequestable(const IRequestable& copy) : fromMod(copy.fromMod), ID(copy.ID), mode(copy.mode), objectVersion(copy.objectVersion) {}
	
	inline IRequestable(const IRequestable&& rvalreference) noexcept : fromMod(std::move(rvalreference.fromMod)), ID(std::move(rvalreference.ID)),
		mode(std::move(rvalreference.mode)), objectVersion(std::move(rvalreference.objectVersion)) {}
	
	inline IRequestable& operator=(const IRequestable& left) {
		fromMod = left.fromMod;
		ID = left.ID;
		mode = left.mode;
		objectVersion = left.objectVersion;
		return *this;
	}

	inline virtual Core::String getName() const
	{
		return "";
	}

	inline virtual Core::String getValue() const
	{
		return "";
	}

	virtual ~IRequestable() = default;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(fromMod);
		ar(ID);
		ar(mode);
		ar(objectVersion);
	}

	template<class Archive>
	void load(Archive& ar)
	{
		ar(fromMod);
		ar(ID);
		ar(mode);
		ar(objectVersion);
	}
};


#endif
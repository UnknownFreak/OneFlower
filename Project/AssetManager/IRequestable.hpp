#ifndef IREQUESTABLE_HPP
#define IREQUESTABLE_HPP
#include <Core\String.hpp>
#include "ObjectSaveMode.hpp"

struct IRequestable
{


	Core::String fromMod;
	size_t ID;
	ObjectSaveMode mode = ObjectSaveMode::ADD;

	inline IRequestable() : fromMod(""), ID(0) {}
	inline IRequestable(const Core::String fromMod, const size_t ID) : fromMod(fromMod), ID(ID) {}
	inline IRequestable(const IRequestable& copy) : fromMod(copy.fromMod), ID(copy.ID), mode(copy.mode) {}
	
	inline IRequestable(const IRequestable&& rvalreference) noexcept : fromMod(std::move(rvalreference.fromMod)), ID(std::move(rvalreference.ID)), mode(std::move(rvalreference.mode)) {}
	
	inline IRequestable& operator=(const IRequestable& left) {
		fromMod = left.fromMod;
		ID = left.ID;
		mode = left.mode;

		return *this;
	}

	

	virtual ~IRequestable() = default;

	template<class Archive>
	void save(Archive& ar) const
	{
		ar(fromMod);
		ar(ID);
		ar(mode);
	}

	template<class Archive>
	void load(Archive& ar)
	{
		ar(fromMod);
		ar(ID);
		ar(mode);
	}
};


#endif
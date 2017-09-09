#ifndef ISAVEABLE_HPP
#define ISAVEABLE_HPP
#include <Core\String.hpp>
#include "ObjectSaveMode.hpp"

struct ISaveable
{


	Core::String fromMod;
	size_t ID;
	ObjectSaveMode mode = ObjectSaveMode::ADD;

	inline ISaveable() : fromMod(""), ID(0) {}
	inline ISaveable(const Core::String fromMod, const size_t ID) : fromMod(fromMod), ID(ID) {}
	inline ISaveable(const ISaveable& copy) : fromMod(copy.fromMod), ID(copy.ID), mode(copy.mode) {}
	
	inline ISaveable(const ISaveable&& rvalreference) noexcept : fromMod(std::move(rvalreference.fromMod)), ID(std::move(rvalreference.ID)), mode(std::move(rvalreference.mode)) {}
	
	inline ISaveable& operator=(const ISaveable& left) {
		fromMod = left.fromMod;
		ID = left.ID;
		mode = left.mode;

		return *this;
	}

	

	virtual ~ISaveable() = default;

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
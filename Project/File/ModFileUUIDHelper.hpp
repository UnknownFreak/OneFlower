#ifndef ModFileUUIDHelper_HPP
#define ModFileUUIDHelper_HPP
#include <Helpers/String.hpp>
#include <Helpers/uuid.hpp>

struct ModFileUUIDHelper
{

	ModFileUUIDHelper() : ModFileUUIDHelper("", Core::uuid::nil()) {};
	ModFileUUIDHelper(const Core::String& name, const Core::uuid& uuid) : name(name), uuid(uuid) {};
	ModFileUUIDHelper(const ModFileUUIDHelper& copy) : ModFileUUIDHelper(copy.name, copy.uuid) {};
	ModFileUUIDHelper& operator=(const ModFileUUIDHelper& right) 
	{
		name = right.name;
		uuid = right.uuid;
		return *this;
	};

	bool operator<(const ModFileUUIDHelper& other) const
	{
		return uuid < other.uuid;
	}

	bool operator==(const ModFileUUIDHelper& other) const
	{
		return uuid == other.uuid && name == other.name;
	}

	Core::String name;
	Core::uuid uuid;
	
	template <class Archive>
	void save(Archive& saver) const
	{
		saver(name);
		saver(uuid);
	}

	template <class Archive>
	void load(Archive& loader)
	{
		loader(name);
		loader(uuid);
	}

	Core::String operator()() const
	{
		return "{" + name + "," + uuid.to_string() + "}";
	}
};

namespace std
{
	template <>
	struct hash<ModFileUUIDHelper>
	{
		std::size_t operator()(ModFileUUIDHelper const& helper) const
		{
			return std::hash<Core::String>()(helper());
		}
	};
}

#endif
#ifndef ModFileUUIDHelper_HPP
#define ModFileUUIDHelper_HPP
#include <utils/common/String.hpp>
#include <utils/common/uuid.hpp>

namespace File::Mod
{

	struct ModFileUUIDHelper
	{

		ModFileUUIDHelper() : ModFileUUIDHelper("", of::common::uuid::nil()) {};
		ModFileUUIDHelper(const of::common::String& name, const of::common::uuid& uuid) : name(name), uuid(uuid) {};
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

		bool isValid() const
		{
			return !uuid.is_nil() && name != "";
		}

		of::common::String name;
		of::common::uuid uuid;

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

		inline of::common::String operator()(const bool& truncateUuidString=false) const
		{
			if (truncateUuidString)
			{
				return "[\"" + name + "\"," + of::common::truncate(uuid.to_string()) + "]";
			}
			return "[\"" + name + "\"," + uuid.to_string() + "]";
		}
	};
};

namespace std
{
	template <>
	struct hash<File::Mod::ModFileUUIDHelper>
	{
		std::size_t operator()(File::Mod::ModFileUUIDHelper const& helper) const
		{
			return std::hash<of::common::String>()(helper());
		}
	};
}

#endif
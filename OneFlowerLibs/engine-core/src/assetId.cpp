#include <asset/assetId.hpp>

namespace of::asset
{
	AssetId::AssetId() : AssetId("", common::uuid::nil()) {}

	AssetId::AssetId(const common::uuid& uuid) : AssetId("", uuid) {};

	AssetId::AssetId(const common::String& name, const common::uuid& uuid) : name(name), uuid(uuid) {}

	AssetId::AssetId(const AssetId& copy) : AssetId(copy.name, copy.uuid) {}

	AssetId& AssetId::operator=(const AssetId& right)
	{
		name = right.name;
		uuid = right.uuid;
		return *this;
	}

	bool AssetId::operator<(const AssetId& other) const
	{
		return uuid < other.uuid;
	}

	bool AssetId::operator==(const AssetId& other) const
	{
		return uuid == other.uuid && name == other.name;
	}

	bool AssetId::isValid() const
	{
		return !uuid.is_nil() && name != "";
	}

	common::String AssetId::operator()(const bool& truncateUuidString) const
	{
		if (truncateUuidString)
		{
			return "[\"" + name + "\"," + common::truncate(uuid.to_string()) + "]";
		}
		return "[\"" + name + "\"," + uuid.to_string() + "]";
	}
}
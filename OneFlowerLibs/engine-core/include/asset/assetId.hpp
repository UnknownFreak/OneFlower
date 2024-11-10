#pragma once

#include <utils/common/String.hpp>
#include <utils/common/uuid.hpp>

namespace of::asset
{
	struct AssetId
	{

		common::String name;
		common::uuid uuid;

		AssetId();
		AssetId(const common::uuid& uuid);
		AssetId(const common::String& name, const common::uuid& uuid);
		AssetId(const AssetId& copy);
		AssetId& operator=(const AssetId& right);

		bool operator<(const AssetId& other) const;

		bool operator==(const AssetId& other) const;

		bool isValid() const;

		common::String operator()(const bool& truncateUuidString = false) const;

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
	};
};

namespace std
{
	template <>
	struct hash<of::asset::AssetId>
	{
		inline std::size_t operator()(of::asset::AssetId const& helper) const
		{
			return std::hash<of::common::String>()(helper());
		}
	};
}

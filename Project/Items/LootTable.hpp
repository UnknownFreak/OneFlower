#ifndef LootTable_HPP
#define LootTable_HPP

#include <unordered_map>

#include <asset/assetId.hpp>
#include <asset/iAsset.hpp>

struct DropConstraint
{
	double rateChance;
	// constraint
};

struct ItemDrop
{
	int minDropCount, maxDropCount;
	of::asset::AssetId itemId;
	bool instantPickup;

	bool operator==(const ItemDrop& other) const
	{
		return itemId == other.itemId;
	}
};

namespace std
{
	template <>
	struct hash<ItemDrop>
	{
		std::size_t operator()(ItemDrop const& drop) const
		{
			return std::hash<of::asset::AssetId>()(drop.itemId);
		}
	};
}

namespace Items
{
	class LootTable : public of::asset::IAsset
	{
	public:

		std::unordered_map<ItemDrop, DropConstraint> lootTable;

		std::unordered_map<of::asset::AssetId, size_t> generateDrops() const;

		// Inherited via IRequestable
		virtual of::asset::TypeInfo getTrait() const override;
	};
}

#endif
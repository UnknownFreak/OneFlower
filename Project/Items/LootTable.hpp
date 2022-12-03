#ifndef LootTable_HPP
#define LootTable_HPP
#include <file/Archive/Requestable.hpp>
#include <file/FileId.hpp>

struct DropConstraint
{
	double rateChance;
	// constraint
};

struct ItemDrop
{
	int minDropCount, maxDropCount;
	of::file::FileId itemId;
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
			return std::hash<of::file::FileId>()(drop.itemId);
		}
	};
}

namespace Items
{
	class LootTable : public of::file::archive::Requestable
	{
	public:

		std::unordered_map<ItemDrop, DropConstraint> lootTable;

		std::unordered_map<of::file::FileId, size_t> generateDrops() const;

		// Inherited via IRequestable
		virtual of::file::archive::TypeInfo getTrait() const override;
	};
}

#endif
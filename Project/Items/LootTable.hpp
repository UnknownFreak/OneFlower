#ifndef LootTable_HPP
#define LootTable_HPP
#include <Interfaces/IRequestable.hpp>
#include <File/ModFileUUIDHelper.hpp>

struct DropConstraint
{
	double rateChance;
	// constraint
};

struct ItemDrop
{
	int minDropCount, maxDropCount;
	ModFileUUIDHelper itemId;
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
			return std::hash<ModFileUUIDHelper>()(drop.itemId);
		}
	};
}

namespace Items
{


	class LootTable : public Interfaces::IRequestable
	{
	public:

		std::unordered_map<ItemDrop, DropConstraint> lootTable;

		std::unordered_map<ModFileUUIDHelper, size_t> generateDrops() const;

		// Inherited via IRequestable
		virtual Interfaces::TypeInfo getTrait() const override;
	};
}

#endif
#include "LootTable.hpp"
#include <rng/rng.hpp>

of::common::uuid of::asset::Trait<Items::LootTable>::typeId = of::common::uuid("f496f3a2-bd62-4aa0-880f-439aab7e46af");

std::unordered_map<of::asset::AssetId, size_t> Items::LootTable::generateDrops() const
{
    std::unordered_map<of::asset::AssetId, size_t> loot;
    //auto& gen = Engine::GetModule<of::module::RandomGen>();
    //for (auto& x : lootTable)
    //{
    //    auto chance = gen.random_double(0, 100);
    //    if (chance < x.second.rateChance)
    //    {
    //        size_t stackCount = (size_t) gen.random_int(x.first.minDropCount, x.first.maxDropCount);
    //        if (stackCount)
    //        {
    //            loot[x.first.itemId] = stackCount;
    //        }
    //    }
    //}
    return loot;
}

of::asset::TypeInfo Items::LootTable::getTrait() const
{
    return { of::asset::Trait<Items::LootTable>::typeId };
}

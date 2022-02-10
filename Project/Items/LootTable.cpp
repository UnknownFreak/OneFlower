#include "LootTable.hpp"
#include <Module/EngineModuleManager.hpp>
#include <Module/Random.hpp>

Core::uuid Interfaces::Trait<Items::LootTable>::typeId = Core::uuid("f496f3a2-bd62-4aa0-880f-439aab7e46af");

std::unordered_map<File::Mod::ModFileUUIDHelper, size_t> Items::LootTable::generateDrops() const
{
    std::unordered_map<File::Mod::ModFileUUIDHelper, size_t> loot;
    //auto& gen = Engine::GetModule<EngineModule::RandomGen>();
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

Interfaces::TypeInfo Items::LootTable::getTrait() const
{
    return { Interfaces::Trait<Items::LootTable>::typeId };
}

#include "LootContainer.hpp"

#include <file/Handler.hpp>
#include <file/SaveFile.hpp>

#include <component/render.hpp>
#include <Items/Inventory.hpp>


namespace of::component
{
	void LootContainer::onMessage(const of::object::messaging::Message&)
	{
	}
	void LootContainer::setLooted()
	{
		//TODO: replace with LootedSaveState
		//looted = of::engine::GetModule<of::module::SaveFile>().isLooted(attachedOn->id);
	}

	void LootContainer::loot(object::GameObject* object)
	{
		looted = true;
		// play loot animation
		// set containerId looted in saveState;
		if (isStaticContainer)
		{
			// TODO: replace with LootedSaveState
			//of::engine::GetModule<of::module::SaveFile>().setLooted(attachedOn->id);
		}
		for (auto& x : lootDrops)
		{
			auto tmp = of::engine::GetModule<of::file::Handler>().archive.requestShared<Items::Base>(x.first);
			object->get<of::component::Inventory>()->addItem(tmp, x.second);
		}
	}

	bool LootContainer::isLooted() const
	{
		return looted;
	}
}

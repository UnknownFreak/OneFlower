#include "LootContainer.hpp"

#include <file/Handler.hpp>
#include <module/SaveFile.hpp>

#include <module/ObjectInstanceHandler.hpp>
#include <Graphics/Render.hpp>
#include <Items/Inventory.hpp>

//of::common::uuid of::object::component::IBase<of::object::component::LootContainer>::typeID;
//of::common::String of::object::component::IBase<of::object::component::LootContainer>::componentName = "LootContainer";


namespace of::object::component
{
	void component::LootContainer::onMessage(const of::object::messaging::Message&)
	{
	}
	void LootContainer::setLooted()
	{
		//TODO: replace with LootedSaveState
		//looted = of::engine::GetModule<of::module::SaveFile>().isLooted(attachedOn->id);
	}

	void LootContainer::loot(GameObject* object)
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
			object->get<of::object::component::Inventory>()->addItem(tmp, x.second);
		}
	}

	bool LootContainer::isLooted() const
	{
		return looted;
	}

	void LootContainer::onCollision(GameObject* )
	{
	}

	void LootContainer::Update()
	{
	}

	void LootContainer::Simulate(const float& )
	{
	}

	void LootContainer::onDeath()
	{
	}

	void LootContainer::onDelete()
	{
	}
}

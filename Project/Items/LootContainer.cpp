#include "LootContainer.hpp"

#include <File/Asset/Manager.hpp>
#include <File/SaveFile.hpp>

#include <Object/ObjectInstanceHandler.hpp>
#include <Graphics/Render.hpp>
#include <Items/Inventory.hpp>

Enums::ComponentType Component::IBase<Component::LootContainer>::typeID = Enums::ComponentType::LootContainer;
of::common::String Component::IBase<Component::LootContainer>::componentName = "LootContainer";


namespace Component
{
	void LootContainer::setLooted()
	{
		looted = of::engine::GetModule<File::SaveFile>().isLooted(attachedOn->id);
	}

	void LootContainer::loot(GameObject* object)
	{
		looted = true;
		// play loot animation
		// set containerId looted in saveState;
		if (isStaticContainer)
			of::engine::GetModule<File::SaveFile>().setLooted(attachedOn->id);
		for (auto& x : lootDrops)
		{
			auto tmp = of::engine::GetModule<File::Asset::Manager>().requestor.requestShared<Items::Base>(x.first);
			object->getComponent<Component::Inventory>()->addItem(tmp, x.second);
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

#include "LootContainer.hpp"

#include <File/AssetManagerCore.hpp>
#include <File/SaveFile.hpp>

#include <Object/ObjectInstanceHandler.hpp>
#include <Graphics/Render.hpp>
#include <Items/Inventory.hpp>

Enums::ComponentType Component::IBase<Component::LootContainer>::typeID = Enums::ComponentType::LootContainer;
Core::String Component::IBase<Component::LootContainer>::componentName = "LootContainer";


namespace Component
{
	void LootContainer::setLooted()
	{
		looted = Engine::GetModule<File::SaveFile>().isLooted(attachedOn->id);
	}

	void LootContainer::loot(GameObject* object)
	{
		looted = true;
		// play loot animation
		// set containerId looted in saveState;
		if (isStaticContainer)
			Engine::GetModule<File::SaveFile>().setLooted(attachedOn->id);
		for (auto& x : lootDrops)
		{
			auto tmp = Engine::GetModule<Asset::AssetManager>().requestor.requestShared<Items::Base>(x.first);
			object->getComponent<Component::Inventory>()->addItem(tmp, x.second);
		}
	}

	bool LootContainer::isLooted() const
	{
		return looted;
	}

	void LootContainer::onCollision(Interfaces::ICollider* )
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

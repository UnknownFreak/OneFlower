#include "LootDrop.hpp"

#include <File/Asset/Manager.hpp>

#include <Object/ObjectInstanceHandler.hpp>
#include <Graphics/Render.hpp>
#include <Items/Inventory.hpp>
#include <Items/LootContainer.hpp>


Enums::ComponentType Component::IBase<Component::LootDrop>::typeID = Enums::ComponentType::LootDrop;
of::common::String Component::IBase<Component::LootDrop>::componentName = "LootDrop";

void Component::LootDrop::loot(GameObject* object)
{
	looted = true;
	for (auto& x : lootDrops)
	{
		auto tmp = Engine::GetModule<File::Asset::Manager>().requestor.requestShared<Items::Base>(x.first);
		object->getComponent<Component::Inventory>()->addItem(tmp, x.second);
	}
}

bool Component::LootDrop::isLooted() const
{
	return looted;
}

void Component::LootDrop::onCollision(GameObject* )
{
}

void Component::LootDrop::Update()
{
}

void Component::LootDrop::Simulate(const float& )
{
}

void Component::LootDrop::onDeath()
{
	lootDrops = table.generateDrops();
}

void Component::LootDrop::onDelete()
{
	if (!looted && lootDrops.size() != 0)
	{
		auto go = Engine::GetModule<EngineModule::ObjectInstanceHandler>().addObject();
		go->addComponent<Render>();
		go->getComponent<Component::Transform>()->pos = attachedOn->getComponent<Component::Transform>()->pos;
		go->addComponent<Component::LootContainer>();
		// TODO: Attach loot to container & set proper rendering texture via global prefab perhaps?
	}
}

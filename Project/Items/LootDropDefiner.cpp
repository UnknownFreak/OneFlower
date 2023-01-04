#include "LootDrop.hpp"

#include <file/Handler.hpp>

#include <module/ObjectInstanceHandler.hpp>
#include <Graphics/Render.hpp>
#include <Items/Inventory.hpp>
#include <Items/LootContainer.hpp>


//of::common::uuid of::object::component::IBase<of::object::component::LootDrop>::typeID;
//of::common::String of::object::component::IBase<of::object::component::LootDrop>::componentName = "LootDrop";


namespace of::object::component
{

	void LootDrop::onMessage(const of::object::messaging::Message&)
	{
	}

	void LootDrop::loot(GameObject* object)
	{
		looted = true;
		for (auto& x : lootDrops)
		{
			auto tmp = of::engine::GetModule<of::file::Handler>().archive.requestShared<Items::Base>(x.first);
			object->get<of::object::component::Inventory>()->addItem(tmp, x.second);
		}
	}

	bool LootDrop::isLooted() const
	{
		return looted;
	}

	void LootDrop::onCollision(GameObject*)
	{
	}

	void LootDrop::Update()
	{
	}

	void LootDrop::Simulate(const float&)
	{
	}

	void LootDrop::onDeath()
	{
		lootDrops = table.generateDrops();
	}

	void LootDrop::onDelete()
	{
		if (!looted && lootDrops.size() != 0)
		{
			auto go = of::engine::GetModule<of::module::ObjectInstanceHandler>().addObject();
			go->add<Render>();
			go->get<of::object::component::Transform>()->pos = attachedOn->get<of::object::component::Transform>()->pos;
			go->add<of::object::component::LootContainer>();
			// TODO: Attach loot to container & set proper rendering texture via global prefab perhaps?
		}
	}
}
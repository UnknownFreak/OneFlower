#include "LootDrop.hpp"

#include <file/Handler.hpp>

#include <module/ObjectInstanceHandler.hpp>
#include <object/component/Render.hpp>
#include <Items/Inventory.hpp>
#include <Items/LootContainer.hpp>


namespace of::object::component
{

	void LootDrop::onMessage(const of::object::messaging::Message& message)
	{
		using namespace of::object::messaging;

		if (message.messageTopic == Topic::of(Topics::ON_DEATH))
		{
			lootDrops = table.generateDrops();
		}
		else if (message.messageTopic == Topic::of(Topics::ON_DELETE))
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
}
#include "LootDrop.hpp"

#include <file/Handler.hpp>

#include <object/InstanceHandler.hpp>
#include <component/render.hpp>
#include <Items/Inventory.hpp>
#include <Items/LootContainer.hpp>


namespace of::component
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
				auto go = of::object::addObject();
				go->add<Render>();
				go->get<of::component::Transform>()->pos = attachedOn->get<of::component::Transform>()->pos;
				go->add<of::component::LootContainer>();
				// TODO: Attach loot to container & set proper rendering texture via global prefab perhaps?
			}
		}
	}

	void LootDrop::loot(object::GameObject* object)
	{
		looted = true;
		for (auto& x : lootDrops)
		{
			auto tmp = of::engine::GetModule<of::file::Handler>().archive.requestShared<Items::Base>(x.first);
			object->get<of::component::Inventory>()->addItem(tmp, x.second);
		}
	}

	bool LootDrop::isLooted() const
	{
		return looted;
	}
}
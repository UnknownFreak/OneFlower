#include "Interactable.hpp"
#include <Object/GameObject.hpp>

#include <object/InstanceHandler.hpp>

namespace of::component
{
	bool Interactable::interact(const Object::Interaction& interaction)
	{
		using namespace of::object::messaging;
		if (interaction.interactionRequirement.operator bool() &&
			interaction.interactionRequirement->fullfilled())
		{
			interactionState = interaction.interactionState;

			attachedOn->post(Topic::of(Topics::SET_ANIMATION), std::make_shared<StringBody>(interaction.interactionAnimation));

			if (interaction.interactionTrigger.operator bool())
				interaction.interactionTrigger->execute();
			auto& instanceHandler = of::object::get();
			for (auto& [objectId, toggleState, reverse, repeat] : interaction.interactions)
			{
				if (instanceHandler.exists(objectId))
				{
					auto object = instanceHandler.getObject(objectId);
					if (toggleState)
						object->toggleObjectState();
					else
					{
						// TODO: fix message for interaction
						//object->post()
						//object->interact(reverse, repeat);
					}
						
				}
			}
			return true;
		}
		return false;
	}

	void Interactable::interact(object::GameObject& interactable)
	{
		using namespace of::object::messaging;
		auto& [normalInteraction, _] = interactions[interactionState];
		if (interact(normalInteraction))
			interactable.post(Topic::of(Topics::SET_ANIMATION), std::make_shared<StringBody>(normalInteraction.actorAnimation));
			//interactable.sendMessage("Anim", normalInteraction.actorAnimation);
	}
	void Interactable::interact(const bool& reverse, const short& repeat)
	{
		repeat;
		auto& [normalInteraction, reversedInteraction] = interactions[interactionState];

		if (reverse)
		{
			interact(reversedInteraction);
		}
		else
		{
			interact(normalInteraction);
		}
	}
}
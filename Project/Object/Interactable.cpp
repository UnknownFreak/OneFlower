#include "Interactable.hpp"
#include <Object/GameObject.hpp>

#include <Object/ObjectInstanceHandler.hpp>

Enums::ComponentType Component::IBase<Component::Interactable>::typeID = Enums::ComponentType::Interactable;
Core::String Component::IBase<Component::Interactable>::componentName = "Interactable";

namespace Component
{
	bool Interactable::interact(const Object::Interaction& interaction)
	{
		if (interaction.interactionRequirement.operator bool() &&
			interaction.interactionRequirement->fullfilled())
		{
			interactionState = interaction.interactionState;

			attachedOn->sendMessage("Anim", interaction.interactionAnimation);

			if (interaction.interactionTrigger.operator bool())
				interaction.interactionTrigger->execute();
			auto& instanceHandler = Engine::GetModule<EngineModule::ObjectInstanceHandler>();
			for (auto& [objectId, toggleState, reverse, repeat] : interaction.interactions)
			{
				if (instanceHandler.exists(objectId))
				{
					auto object = instanceHandler.getObject(objectId);
					if (toggleState)
						object->toggleObjectState();
					else
						object->interact(reverse, repeat);
				}
			}
			return true;
		}
		return false;
	}
	void Interactable::interact(GameObject& interactable)
	{
		auto& [normalInteraction, _] = interactions[interactionState];
		if (interact(normalInteraction))
			interactable.sendMessage("Anim", normalInteraction.actorAnimation);
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
	void Interactable::onCollision(Interfaces::ICollider*)
	{
	}
	void Interactable::Update()
	{
	}
	void Interactable::Simulate(const float&)
	{
	}
	void Interactable::onDeath()
	{
	}
}
#include "PlayerInteractionPrompt.hpp"

#include <Object/GameObject.hpp>

#include <Graphics/UI/UIHandler.hpp>
#include <Graphics/UI/DialogScreen.hpp>
#include <module/resource/TextureLoader.hpp>
#include <Items/Inventory.hpp>

PlayerInteractionPrompt::PlayerInteractionPrompt()
{
	texture = of::engine::GetModule<of::module::texture::Loader>().requestTexture("DialogPrompt.png", of::module::Settings::uiTexturePath);

}

PlayerInteractionPrompt::PlayerInteractionPrompt(const PlayerInteractionPrompt& )
{
}

void PlayerInteractionPrompt::onMessage(const of::object::messaging::Message&)
{
}

bool PlayerInteractionPrompt::doInteraction(const Enums::InteractionOption& navigate)
{
	if (showPrompt && dialog )
	{
		auto& handler = of::engine::GetModule<Graphics::UI::UIHandler>();
		if (handler.isContextAvailable(Enums::UIContextNames::DialogScreen))
		{
			Graphics::UI::DialogScreen* uicontext = handler.getUIContext<Graphics::UI::DialogScreen>(Enums::UIContextNames::DialogScreen);
			if (!uicontext->isVisible() && navigate == Enums::InteractionOption::Select)
				uicontext->show(dialog);
			else
				uicontext->readInput(navigate);
		}
		else
		{
			if (navigate == Enums::InteractionOption::Select)
				handler.addUIContext(Enums::UIContextNames::DialogScreen, std::make_unique<Graphics::UI::DialogScreen>(dialog));
		}
		return true;
	}
	else if(showPrompt && lootDrop && !lootDrop->isLooted()) 
	{
		lootDrop->loot(attachedOn);
		return true;
	}
	else if (showPrompt && lootContainer && !lootContainer->isLooted())
	{
		lootContainer->loot(attachedOn);
		return true;
	}
	return false;
}

void PlayerInteractionPrompt::attachOn(of::object::GameObject* go)
{
	Base::attachOn(go);
}

void PlayerInteractionPrompt::onCollision(of::object::GameObject* theCollidee)
{
	//auto& colliderType = theCollidee->colliderType;
	//if (colliderType == Enums::ColliderType::Entity || colliderType == Enums::ColliderType::StaticEntity)
	{
		
		of::object::GameObject* theObject = theCollidee;
		Dialog* dialogComponent = theObject->get<Dialog>();
		of::object::component::LootDrop* theDrop = theObject->get<of::object::component::LootDrop>();
		of::object::component::LootContainer* theContainer = theObject->get<of::object::component::LootContainer>();
		if (dialogComponent)
		{
			showPrompt = true;
			dialog = dialogComponent;
			lived = 0.f;
			//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
		else if (theDrop)
		{
			of::engine::GetModule<of::module::logger::OneLogger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
			showPrompt = true;
			lootDrop = theDrop;
			lived = 0.f;
			//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
		else if (theContainer)
		{
			of::engine::GetModule<of::module::logger::OneLogger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
			showPrompt = true;
			lootContainer = theContainer;
			lived = 0.f;
			//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
		// TODO: add logic for interactables like, buttons/ levers/ portals?
		//*/
	}
}

void PlayerInteractionPrompt::Update()
{
	if (showPrompt == false && dialog)
	{
		dialog = nullptr;
		auto& handler = of::engine::GetModule<Graphics::UI::UIHandler>();
		if (handler.isContextAvailable(Enums::UIContextNames::DialogScreen))
		{
			Graphics::UI::DialogScreen* uicontext = handler.getUIContext<Graphics::UI::DialogScreen>(Enums::UIContextNames::DialogScreen);
			if (uicontext && uicontext->isVisible())
			{
				uicontext->toggleVisible();
			}
		}
	}
}

void PlayerInteractionPrompt::Simulate(const float&dt)
{
	lived += dt;
	showPrompt = lived < ttl;
}

void PlayerInteractionPrompt::onDeath()
{
}

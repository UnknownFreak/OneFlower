#include "PlayerInteractionPrompt.hpp"

#include <Object/GameObject.hpp>

#include <Graphics/UI/UIHandler.hpp>
#include <Graphics/UI/DialogScreen.hpp>
#include <File/Resource/TextureLoader.hpp>
#include <Items/Inventory.hpp>

Enums::ComponentType Component::IBase<PlayerInteractionPrompt>::typeID = Enums::ComponentType::PlayerInteraction;
of::common::String Component::IBase<PlayerInteractionPrompt>::componentName = "PlayerInteractionPrompt";

PlayerInteractionPrompt::PlayerInteractionPrompt()
{
	texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture("DialogPrompt.png", Globals::uiTexturePath);

}

PlayerInteractionPrompt::PlayerInteractionPrompt(const PlayerInteractionPrompt& )
{
}

bool PlayerInteractionPrompt::doInteraction(const Enums::InteractionOption& navigate)
{
	if (showPrompt && dialog )
	{
		auto& handler = Engine::GetModule<Graphics::UI::UIHandler>();
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

void PlayerInteractionPrompt::attachOn(GameObject* go)
{
	Base::attachOn(go);
}

void PlayerInteractionPrompt::onCollision(GameObject* theCollidee)
{
	//auto& colliderType = theCollidee->colliderType;
	//if (colliderType == Enums::ColliderType::Entity || colliderType == Enums::ColliderType::StaticEntity)
	{
		
		GameObject* theObject = theCollidee;
		Dialog* dialogComponent = theObject->getComponent<Dialog>();
		Component::LootDrop* theDrop = theObject->getComponent<Component::LootDrop>();
		Component::LootContainer* theContainer = theObject->getComponent<Component::LootContainer>();
		if (dialogComponent)
		{
			showPrompt = true;
			dialog = dialogComponent;
			lived = 0.f;
			//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
		else if (theDrop)
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
			showPrompt = true;
			lootDrop = theDrop;
			lived = 0.f;
			//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
		else if (theContainer)
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
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
		auto& handler = Engine::GetModule<Graphics::UI::UIHandler>();
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

#include "PlayerInteractionPrompt.hpp"

#include <Object/GameObject.hpp>

#include <Graphics/UI/UIHandler.hpp>
#include <Graphics/UI/DialogScreen.hpp>
#include <module/resource/TextureLoader.hpp>
#include <Items/Inventory.hpp>

#include <courier/courier.hpp>

PlayerInteractionPrompt::PlayerInteractionPrompt()
{
	texture = of::engine::GetModule<of::module::texture::Loader>().requestTexture("DialogPrompt.png", of::module::Settings::uiTexturePath);

}

PlayerInteractionPrompt::PlayerInteractionPrompt(const PlayerInteractionPrompt& )
{
}

void PlayerInteractionPrompt::onMessage(const of::object::messaging::Message& message)
{
	using namespace of::object::messaging;
	if (message.messageTopic == Topic::of(Topics::ON_COLLISION) && message.messageBody->bodyType == BodyType::GAMEOBJECT_PTR)
	{
		//auto& colliderType = theCollidee->colliderType;
//if (colliderType == Enums::ColliderType::Entity || colliderType == Enums::ColliderType::StaticEntity)
		{

			of::object::GameObject* theObject = (of::object::GameObject*) ((GameObjectPtr*)message.messageBody.get())->go;
			Dialog* dialogComponent = theObject->get<Dialog>();
			of::component::LootDrop* theDrop = theObject->get<of::component::LootDrop>();
			of::component::LootContainer* theContainer = theObject->get<of::component::LootContainer>();
			if (dialogComponent)
			{
				showPrompt = true;
				dialog = dialogComponent;
				lived = 0.f;
				//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
			}
			else if (theDrop)
			{
				of::engine::GetModule<of::logger::Logger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
				showPrompt = true;
				lootDrop = theDrop;
				lived = 0.f;
				//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
			}
			else if (theContainer)
			{
				of::engine::GetModule<of::logger::Logger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
				showPrompt = true;
				lootContainer = theContainer;
				lived = 0.f;
				//updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
			}
			// TODO: add logic for interactables like, buttons/ levers/ portals?
			//*/
		}
	}
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

void PlayerInteractionPrompt::update(const float&dt)
{
	lived += dt;
	showPrompt = lived < ttl;


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

void PlayerInteractionPrompt::attached()
{
	of::engine::GetModule<of::courier::Courier>().addSubscriber(of::courier::Topic::Update,
		of::courier::Subscriber(instanceId, isAlive(),
			[this](const of::courier::Message& msg) {update(msg.get<float>()); }
	));
}

void PlayerInteractionPrompt::initialize()
{

}

void PlayerInteractionPrompt::deconstruct()
{
	of::engine::GetModule<of::courier::Courier>().removeSubscriber(of::courier::Topic::Update, instanceId);

}
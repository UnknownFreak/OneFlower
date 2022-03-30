#include "PlayerInteractionPrompt.hpp"

#include <Object/GameObject.hpp>
#include <Physics/Colliders/EntityCollider.hpp>

#include <Graphics/UI/UIHandler.hpp>
#include <Graphics/UI/DialogScreen.hpp>
#include <File/Resource/TextureLoader.hpp>
#include <Items/Inventory.hpp>

Enums::ComponentType Component::IBase<PlayerInteractionPrompt>::typeID = Enums::ComponentType::PlayerInteraction;
Core::String Component::IBase<PlayerInteractionPrompt>::componentName = "PlayerInteractionPrompt";

void PlayerInteractionPrompt::updatePromptIcon(sf::VertexArray& va, const Core::Vector2f& postision)
{
	va[0].position = { postision.x, postision.y };
	va[1].position = { postision.x, postision.y + iconSize };
	va[2].position = { postision.x + iconSize, postision.y + iconSize };
	va[3].position = { postision.x + iconSize, postision.y };
}

PlayerInteractionPrompt::PlayerInteractionPrompt() : Renderable({ 0,0,16.f,16.f }), dialogInteractionPromptIcon(sf::PrimitiveType::Quads, 4)
{
	texture = Engine::GetModule<File::Resource::Texture::Loader>().requestTexture("DialogPrompt.png", Globals::uiTexturePath);
	auto texSize = texture.get()->getSize();
	dialogInteractionPromptIcon[0].texCoords = { 0,0 };
	dialogInteractionPromptIcon[1].texCoords = { 0, float(texSize.y) };
	dialogInteractionPromptIcon[2].texCoords = { float(texSize.x), float(texSize.y)};
	dialogInteractionPromptIcon[3].texCoords = { float(texSize.y), 0 };
}

PlayerInteractionPrompt::PlayerInteractionPrompt(const PlayerInteractionPrompt& copy) : Renderable(copy), dialogInteractionPromptIcon(copy.dialogInteractionPromptIcon)
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

void PlayerInteractionPrompt::onCollision(Interfaces::ICollider* theCollidee)
{
	auto& colliderType = theCollidee->colliderType;
	if (colliderType == Enums::ColliderType::Entity || colliderType == Enums::ColliderType::StaticEntity)
	{
		GameObject* theObject = ((Collider*)theCollidee)->attachedOn;
		Dialog* dialogComponent = theObject->getComponent<Dialog>();
		Component::LootDrop* theDrop = theObject->getComponent<Component::LootDrop>();
		Component::LootContainer* theContainer = theObject->getComponent<Component::LootContainer>();
		if (dialogComponent)
		{
			showPrompt = true;
			dialog = dialogComponent;
			lived = 0.f;
			updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
		else if (theDrop)
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
			showPrompt = true;
			lootDrop = theDrop;
			lived = 0.f;
			updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
		else if (theContainer)
		{
			Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("Looting has no toggle switch implemented yet... log for now so it can be seen in the logs...", __FILE__, __LINE__);
			showPrompt = true;
			lootContainer = theContainer;
			lived = 0.f;
			updatePromptIcon(dialogInteractionPromptIcon, theObject->getComponent<Component::Transform>()->buffered.toVector2());
		}
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

void PlayerInteractionPrompt::draw(sf::RenderTarget& target, sf::RenderStates ) const
{
	if (showPrompt)
	{
		if (dialog)
			target.draw(dialogInteractionPromptIcon, texture.get());
		else if (lootDrop || lootContainer)
			target.draw(lootInteractionPromptIcon, texture.get());
		else
			target.draw(useInteractionPromptIcon, texture.get());
	}
}

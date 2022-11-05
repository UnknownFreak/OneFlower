#ifndef PlayerInteractionPromptComponent_HPP
#define PlayerInteractionPromptComponent_HPP

#include <Helpers/Enum/InteractionOption.hpp>

#include <Object/IBaseComponent.hpp>
#include <Object/Transform.hpp>

#include "Model.hpp"
#include "Dialog.hpp"
#include <Items/LootDrop.hpp>
#include <Items/LootContainer.hpp>

class PlayerInteractionPrompt : public Component::IBase<PlayerInteractionPrompt>
{
	bool showPrompt = false;
	Dialog* dialog = nullptr;
	Component::LootDrop* lootDrop = nullptr;
	Component::LootContainer* lootContainer = nullptr;
	Graphics::Model interactionModel;
	std::shared_ptr<swizzle::gfx::Texture> texture;
	float iconSize = 32.f;
	float ttl = 0.1f;
	float lived = 0.f;


public:

	PlayerInteractionPrompt();
	PlayerInteractionPrompt(const PlayerInteractionPrompt& copy);
	~PlayerInteractionPrompt() = default;

	virtual PlayerInteractionPrompt* copy() const override
	{
		return new PlayerInteractionPrompt(*this);
	}

	bool doInteraction(const Enums::InteractionOption& navigate);

	// maybe not needed
	void attachOn(GameObject* go);
	// Inherited via IBase
	virtual void onCollision(GameObject* the_collidee) override;
	virtual void Update() override;
	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;

};

#endif
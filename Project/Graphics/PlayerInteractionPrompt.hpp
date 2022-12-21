#ifndef PlayerInteractionPromptComponent_HPP
#define PlayerInteractionPromptComponent_HPP

#include <Helpers/Enum/InteractionOption.hpp>

#include <object/component/IBaseComponent.hpp>
#include <object/component/Transform.hpp>

#include "Model.hpp"
#include "Dialog.hpp"
#include <Items/LootDrop.hpp>
#include <Items/LootContainer.hpp>

class PlayerInteractionPrompt : public of::object::component::IBase<PlayerInteractionPrompt>
{
	bool showPrompt = false;
	Dialog* dialog = nullptr;
	of::object::component::LootDrop* lootDrop = nullptr;
	of::object::component::LootContainer* lootContainer = nullptr;
	Graphics::Model interactionModel;
	std::shared_ptr<swizzle::gfx::Texture> texture;
	float iconSize = 32.f;
	float ttl = 0.1f;
	float lived = 0.f;

	virtual void onMessage(const of::object::messaging::Message& message) override;
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
	void attachOn(of::object::GameObject* go);
	// Inherited via IBase
	virtual void onCollision(of::object::GameObject* the_collidee) override;
	virtual void Update() override;
	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;

};

#endif
#ifndef PlayerInteractionPromptComponent_HPP
#define PlayerInteractionPromptComponent_HPP

#include <Helpers/Enum/InteractionOption.hpp>

#include "Renderable.hpp"
#include <Object/IBaseComponent.hpp>
#include <Object/Transform.hpp>

#include "Dialog.hpp"
#include <Items/LootDrop.hpp>
#include <Items/LootContainer.hpp>

class PlayerInteractionPrompt :public Renderable, public Component::IBase<PlayerInteractionPrompt>
{
	bool showPrompt = false;
	Dialog* dialog = nullptr;
	Component::LootDrop* lootDrop = nullptr;
	Component::LootContainer* lootContainer = nullptr;
	std::shared_ptr<sf::Texture> texture;
	sf::VertexArray dialogInteractionPromptIcon;
	sf::VertexArray lootInteractionPromptIcon;
	sf::VertexArray useInteractionPromptIcon;
	float iconSize = 32.f;
	float ttl = 0.1f;
	float lived = 0.f;

	void updatePromptIcon(sf::VertexArray& va, const Core::Vector2f& postision);

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
	virtual void onCollision(Interfaces::ICollider* the_collidee) override;
	virtual void Update() override;
	virtual void Simulate(const float& fElapsedTime) override;
	virtual void onDeath() override;

	// Inherited via Renderable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	//void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
#pragma once

#include <Object/Transform.hpp>
#include <Interfaces/ICollider.hpp>
#include <Interfaces/IUpdateable.hpp>
#include <Module/Globals.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class TileCollider : public Interfaces::ICollider, public Interfaces::IUpdateable
{
	Component::Transform t;
public:

	TileCollider(const Core::Vector3f& pos, const Core::Vector2f& size = { Globals::MAX_SIZE, Globals::MAX_SIZE },
 const Enums::ColliderType& colliderType = Enums::ColliderType::Void, const bool& isRoof=false);

	~TileCollider();

	// Inherited via ICollider
	virtual void doParentSimulate(const float& fElapsedTime) override;

	// Inherited via IUpdateable
	virtual void Update() override;

	void buildRenderableHitbox(sf::VertexArray& arr) const;
};
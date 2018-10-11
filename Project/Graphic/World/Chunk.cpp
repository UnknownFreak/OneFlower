#include "Chunk.hpp"

#include <Core/Component/GameObject.h>
#include <Core\Component\TransformComponent.hpp>
#include <Graphic/Component/RenderComponent.h>

float Chunk::size = 2048.f;

Chunk::Chunk() : Chunk({0, 0})
{
}

Chunk::Chunk(Core::Vector2 position) : chunkPosition(position), IDrawableCollider(chunkPosition.x, chunkPosition.y, size, size), tiles(position.x, position.y, size, size)
{
}

void Chunk::setNeighbourChunk(Chunk & neighbour, const Neighbour side)
{
	neighbours[side] = &neighbour;
}

void Chunk::Update()
{
	for (GameObject* go : gameObjects)
	{
		Component::Transform* tc = go->GetComponent<Component::Transform>();
		Component::RenderComponent* rc = go->GetComponent<Component::RenderComponent>();
		if (rc)
		{
			// We ignore nullcheck on model here. Access Violation if we have invalid address.
			// A renderComponent with no model is already bad. 
			rc->model->setPosition(tc->position);
			rc->updateFrame(30); // hardcoded for now, use parameter to get the last update_ms speed to get correct delta.
		}
		// Update runs for all chunks (in that zone)
		// Draw runs for the chunks in view.
		// update logic here for gameobjects. Move them, update their animations etc.
		// double loops, one for update one for drawing, there will be one updater thread to update the gameobjects every 1/60 (120) seconds.
		// while drawing occurs every 1/30 (60) seconds.
		// even more optimal, separate all objects with no collider and no animation, that means less objects to update.
		// Tags can solve this. 
	}
}

void Chunk::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(tiles, states);
	for (GameObject* go : gameObjects)
	{
		Component::RenderComponent* rc = go->GetComponent<Component::RenderComponent>();
		if (rc)
			target.draw(*rc->model);
	}
}

void Chunk::addGameObject(const Asset::Prefab & prefabData, const Database::Prefab& prefabPosition)
{
	GameObject* go = prefabData.createFromPrefab();
	go->GetComponent<Component::Transform>()->position = prefabPosition.pos;
	gameObjects.push_back(go);
}

void Chunk::Simulate()
{
	tiles.update();
}

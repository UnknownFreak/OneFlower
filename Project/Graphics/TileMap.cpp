#include "TileMap.hpp"

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const sf::Shader* orig = states.shader;
	const sf::Texture* origTex = states.texture;
	for (auto& f : culledFloor)
	{
		states.texture = textures.at(f.first).get();
		target.draw(f.second, states);
	}
	for (auto& w : culledWalls)
	{
		states.texture = textures.at(w.first).get();
		target.draw(w.second, states);
	}

	states.shader = orig;
	states.texture = origTex;
	if (renderHitboxes)
		target.draw(culledHitboxes, states);

	for (auto& collider : colliders)
		target.draw(*collider.get(), states);

}

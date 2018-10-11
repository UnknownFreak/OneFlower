#pragma once
#include <Core/Vector.h>
#include <Core\IDrawableCollider.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
namespace World
{
	namespace Grid
	{
		struct Tile : public IDrawableCollider<Tile>
		{
			enum Type
			{
				Blank,
				Block,
				Platform,
				Slope
			};

			sf::RectangleShape s;

			Core::Vector2 pos;
			Tile();
			Tile(float x, float y);
			Tile(float x, float y, Type t);
			Tile(Core::Vector2 pos);
			Tile(Core::Vector2 pos, Type t);
			Tile(const Tile& copy);
			Tile& operator=(const Tile& copy);
			Type type;
			float size = 16.0;

			// Inherited via IDrawableCollider
			virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
		};
	}
}
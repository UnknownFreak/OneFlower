#pragma once
#include <Core/Vector.h>
#include <Physics\IDrawableCollider.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <Asset/SpriteRef.hpp>

namespace World
{
	namespace Grid
	{
		struct Tile : public Physics::IDrawableCollider
		{
			enum Type
			{
				Blank,
				Block,
				Platform,
				Slope,
				NoCollide // Still checks for collision if in a quad-tree, but we check when loading and ignore to add the tile to the quadtree.
			};

			sf::RectangleShape s;

			Core::Vector2 pos;

			Core::String spriteName;
			SpriteRef sprite;

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

			template <class Archive>
			void save(Archive& ar) const
			{
				ar(pos);
				ar(type);
				ar(spriteName);
			}
			
			template <class Archive>
			void load(Archive& ar)
			{
				ar(pos);
				ar(type);
				ar(spriteName);
				sprite.setTexture(Engine::GetModule<Asset::AssetManager>().textureloader.requestTexture(spriteName, Globals::tileTexturePath));
			}
		};
	}
}
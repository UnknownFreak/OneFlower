#include "GridTile.h"

World::Grid::Tile::Tile() : Tile(0, 0) 
{
}

World::Grid::Tile::Tile(Core::Vector2 _pos) : Tile(_pos.x, _pos.y, Grid::Tile::Blank)
{
}

World::Grid::Tile::Tile(Core::Vector2 _pos, World::Grid::Tile::Type t) : Tile(_pos.x, _pos.y, t)
{
}

World::Grid::Tile::Tile(const Tile & copy) : pos(copy.pos.x, copy.pos.y), type(copy.type), IDrawableCollider(pos.x, pos.y, size, size), s(sf::Vector2f(size, size))
{
	s.setPosition(pos.x, pos.y);
}

World::Grid::Tile & World::Grid::Tile::operator=(const World::Grid::Tile & copy)
{
	node = copy.node;
	pos = copy.pos;
	size = copy.size;
	type = copy.type;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = size;
	rect.h = size;
	return *this;
}

void World::Grid::Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(s, states);
}

World::Grid::Tile::Tile(float _x, float _y) : Tile(_x, _y, Grid::Tile::Blank)
{
}

World::Grid::Tile::Tile(float _x, float _y, World::Grid::Tile::Type t) : pos(_x, _y), type(t), IDrawableCollider(pos.x, pos.y, size, size), s(sf::Vector2f(size,size))
{
	s.setPosition(_x, _y);
}
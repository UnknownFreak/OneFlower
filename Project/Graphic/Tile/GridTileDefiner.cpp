#include "GridTile.h"
World::Grid::Tile::Tile(int _x, int _y, World::Grid::Tile::Type t) : pos(_x, _y), type(t)
{
}
World::Grid::Tile::Tile(int _x, int _y) : pos(_x, _y), type(Grid::Tile::Blank)
{
}
World::Grid::Tile::Tile(Core::Vector2i _pos, World::Grid::Tile::Type t) : pos(_pos), type(t)
{
}
World::Grid::Tile::Tile(Core::Vector2i _pos) : pos(_pos), type(Grid::Tile::Blank)
{
}
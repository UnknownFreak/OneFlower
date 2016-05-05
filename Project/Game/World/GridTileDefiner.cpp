#include "GridTile.h"
World::Grid::Tile::Tile(int _x,int _y,World::Grid::Tile::Type t):x(_x),y(_y),type(t)
{

}
World::Grid::Tile::Tile(int _x,int _y) :x(_x),y(_y),type(Grid::Tile::Blank)
{
}
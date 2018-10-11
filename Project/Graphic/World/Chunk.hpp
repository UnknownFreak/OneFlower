#ifndef Chunk_HPP
#define Chunk_HPP

#include <map>

#include <Asset\ISimulatable.hpp>
#include <Asset\IUpdateable.hpp>
#include <Asset/Prefab.hpp>
#include <Asset/Database/DatabaseObjects.hpp>

#include <Core\String.hpp>
#include <Core\Vector.h>
#include <SFML\Graphics\Drawable.hpp>

#include <Physics\IDrawableCollider.hpp>
#include <Physics\QuadTree.hpp>

#include <Graphic\World\GridTile.h>

class GameObject;
class QuadTreeNode;

class Chunk : public Physics::IDrawableCollider, public ISimulatable, public IUpdateable
{

public:
	enum class Neighbour
	{
		BOTTOM_LEFT,
		BOTTOM,
		BOTTM_RIGHT,
		LEFT,
		RIGHT,
		TOP_LEFT,
		TOP,
		TOP_RIGHT,
	};
private:

	inline virtual bool needUpdate() override {
		//once placed a chunk cannot be moved. Therefore the chunk cannot move and does not need an update
		return false;
	}

//#ifdef _UNITTESTS_
	public:
//#endif
	Core::Vector2 chunkPosition;

	QuadTree tiles;
	std::vector<World::Grid::Tile> _tiles;
	std::vector<GameObject*> gameObjects;
	//std::vector<World::Grid::Tile> tiles;
	//QuadTree<NodeObject<sf::Drawable*>*> colliderTree;
	//Decide how gameobjects should be stored inside the chunk.
	//Vector with quadtree or only vector.
	//QuadTree<NodeObject> chunkObjects;
	//std::vector<GameObject*> gameObjects;

	std::map<Neighbour, Chunk*> neighbours;

public:

	Core::String name;

	static float size;

	Chunk();
	Chunk(Core::Vector2 position);

	void setNeighbourChunk(Chunk& neighbour, const Neighbour side);

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	
	void addGameObject(const Asset::Prefab& prefab, const Database::Prefab& prefabPosition);

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(name);
		ar(chunkPosition);
		ar(_tiles);
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(name);
		ar(chunkPosition);
		tiles.resize(chunkPosition, Core::Vector2(size, size));
		ar(_tiles);
		for (World::Grid::Tile& tile : _tiles) // May need iterator here, not tested yet.
		{
#ifndef _EDITOR_
			// In editormode we add all tiles in the chunk, as we may want to edit them, all blank tiles are not added in the "run" mode.
			// However a benefit adding all blank tiles adds future in game modifications to alter terrain with explosions etc. (That has to be saved in the savefile though).
			// But that's another matter. Or there is a special 'modifyable' blank tile to let modders decide.
			// Some zones/chunks may want to have their data protected, while others not. All tiles are available via the _tiles vector so there may be other logic to 
			// insert modified Tiles in the future. 
			if(tile.type != tile.Blank)
#endif
				tiles.insert(*tile);
		}
	}

	// Inherited via ISimulatable
	virtual void Simulate() override;
	// Inherited via IUpdateable
	virtual void Update() override;

};



#endif
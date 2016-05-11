#ifndef Game_H
#define Game_H
#include <vector>
#include <string>
#include <map>
#include "../Vector.h"
#include "World/GridTile.h"
class GameObject;
class Tile;
class Gfx;
class Message;
class RigidComponent;
class HitboxComponent;
namespace Component{class Timer;}
class Game
{
public:
	Game();
	~Game();
	//Get a pointer towards a GameObject from the first match via its name
	GameObject* requestGameObject(std::string);
	//Get a pointer towards a GameObject via a its IdentityCode
	GameObject* requestGameObject(unsigned int ID);
	//Get a pointer towards a GameObject via a copy pointer
	GameObject* requestGameObject(const GameObject* gameObjectPointer);

	GameObject* player;

	//HIGH: Deprecated use the new addGameObject that returns a refrence ptr, for a better memory acess mangement
	void addGameObject(GameObject* entity);
	
	GameObject& addGameObject();

	//void addMotionObject(RigidComponent* entity);
	//void removealMotion(RigidComponent* entity); 
	void addPhysics(HitboxComponent* obj);
	void addPhysics(RigidComponent* obj);
	void removePhysics(RigidComponent* obj);
	void removePhysics(HitboxComponent* obj);
	
	void addTimedObject(Component::Timer* go);
	void removeTimedObject(Component::Timer* go);

	void addGameObject(GameObject entity);
	//This one doesnt work
	void addGameObject(std::string);

	//Return a const pointer of all the gameobject vector
	const std::vector<GameObject*>* requestAllGameObjecVector() const;

	//Editor
	//	void Game::addGameObject(GameObject* entity,Gfx*);

	void requestRemoveal(GameObject* entity);

	void update();
	void movementUpdate();
	void movementGrid();
	void movementRigid();	
	void addSprite(Tile* t,bool isBackground = false);
	void requestRemovealForeground(Tile* t);
	//LOW: Move this out of Physics engine?
	std::vector<HitboxComponent*> hitboxes;
	std::vector<RigidComponent*> rigids;
	//container[x + (y * width)]
	std::vector<World::Grid::Tile> tiles;
	int width = 20;
	int height = 20;

private:
	friend class Mouse;
	//Why do I have two of this? (rigidPointers and Rigid)
	//std::vector<RigidComponent*> rigidPointers;
	std::vector<GameObject*> allGameObjectPointers;
	std::vector<Component::Timer*> timedObject;
	std::vector<GameObject> objects;
	//std::map<GameObject*,int> mapOfGameObjects;

	//What this doing here?: Vector2 pos;
};
#endif
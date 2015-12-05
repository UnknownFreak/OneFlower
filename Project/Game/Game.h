#ifndef Game_H
#define Game_H
#include <vector>
#include <string>
#include <map>
#include "../Vector.h"
class GameObject;
class Tile;
class Gfx;
//class Message;
class Game
{
public:

	~Game();
	//Get a pointer towards a GameObject from the first match via its name
	GameObject* requestGameObject(std::string);
	//Get a pointer towards a GameObject via a its IdentityCode
	GameObject* requestGameObject(unsigned int ID);
	//Get a pointer towards a GameObject via a copy pointer
	GameObject* requestGameObject(const GameObject* gameObjectPointer);

	//GameObject* player;

	//This one work
	void addGameObject(GameObject* entity);
	void addMotionObject(GameObject* entity);

	void addGameObject(GameObject entity);
	//This one doesnt work
	void addGameObject(std::string);

	//Return a const pointer of all the gameobject vector
	const std::vector<GameObject*>* requestAllGameObjecVector() const;

	//Editor
	//	void Game::addGameObject(GameObject* entity,Gfx*);

	void requestRemoveal(GameObject* entity);
	void update();

	void addSprite(Tile* t,bool isBackground = false);
	void requestRemovealForeground(Tile* t);
	void removealMotion(GameObject* entity);
private:
	friend class Mouse;
	std::vector<GameObject*> motionObjectPointers;

	std::vector<GameObject*> allGameObjectPointers;
	//std::map<GameObject*,int> mapOfGameObjects;

	//What this doing here?: Vector2 pos;
};
#endif
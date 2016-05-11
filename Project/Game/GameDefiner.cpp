#include "Game.h"
#include "Component\GameObject.h"
#include "Component\OverheadComponent.hpp"
#include "Tile.h"
#include "Gfx.h"
#include "GUI/Text/Message.hpp"
#include "Component\RenderComponent.h"
#include "Component/HitboxComponent.hpp"
#include "Component\PlayerComponent.hpp"
#include "../Engine.hpp"//std::vector<GameObject> allGameObject;
Game::Game()
{

	for(size_t j = 0; j < height; j++)
	{
		for(size_t i = 0; i < width; i++)
		{
			tiles.push_back(World::Grid::Tile(i,j,World::Grid::Tile::Type::Blank));
		}
	}
	for(size_t i = 0; i < 8; i++)
	{
		tiles[i + (height/2 * width)];
	}
}
Game::~Game()
{
	//TODO: Use find from algorithm
	for(size_t i = 0; i < allGameObjectPointers.size(); i++)
	{
		if(allGameObjectPointers[i])
		{
			delete allGameObjectPointers[i];
			allGameObjectPointers[i] = 0;
		}
	}
}
/*
void Game::addMotionObject(RigidComponent* entity)
{
rigidPointers.push_back(entity);
}
//*/
/*
void Game::removealMotion(RigidComponent* entity)
{
/*
for(size_t i = 0; i < rigidPointers.size(); i++)
{
if(rigidPointers[i] == entity)
{
rigidPointers.erase(rigidPointers.begin() + i);
break;
}
}
}
//*/
void Game::addGameObject(GameObject* entity)
{
	/*
	if(mapOfGameObjects.find(entity) != mapOfGameObjects.end())
	{
	mapOfGameObjects[entity]++;
	}
	else
	{
	mapOfGameObjects.insert(std::pair<GameObject*,int>(entity,1));
	}
	//*/

	allGameObjectPointers.push_back(entity);
	Engine::GUI.addOverhead(entity);
	//Engine::Graphic.insertdrawableObject(entity);
//#ifdef _DEBUG
//	Engine::Window.ListViewer.add(entity);
//	Engine::Window.setGameObject(entity);
//
//#endif
}
GameObject& Game::addGameObject()
{
	objects.push_back(GameObject());
	return objects.back();
}
void Game::addSprite(Tile* t,bool isBackground)
{
	Engine::Graphic.insertdrawableSprite(*t,isBackground);
}
void Game::requestRemovealForeground(Tile* t)
{
	Engine::Graphic.removeFromForegroundList(*t);
}
/*
void Game::addGameObject(GameObject* entity,Gfx* editor)
{
allGameObjectPointers.push_back(entity);
editor->insertdrawableObject(entity);
}
//*/

void Game::addGameObject(std::string name)
{
	//GameObject entity(name);
	/*
	allGameObjectVector.push_back(entity);
	this->allGameObjectPointers.push_back(&allGameObjectVector.at(allGameObjectVector.size() - 1));
	Engine::Graphic.insertdrawableObject(&allGameObjectVector.at(allGameObjectVector.size()-1));
	//*/
}

void Game::requestRemoveal(GameObject* entity)
{
	/*
	if(mapOfGameObjects.find(entity) != mapOfGameObjects.end())
	{
	mapOfGameObjects[entity]--;
	if(mapOfGameObjects[entity] < 1)
	{
	Engine::Graphic.removeFromdrawList(entity);
	mapOfGameObjects.erase(entity);
	for(size_t i = 0; i < allGameObjectPointers.size(); i++)
	{
	if(allGameObjectPointers[i] == entity)
	{
	Engine::Window.ListViewer.remove(entity);
	allGameObjectPointers.erase(allGameObjectPointers.begin() + i);
	Engine::GUI.requestOverheadRemoval(entity);
	delete entity;
	entity = 0;
	break;
	}
	}
	}
	//*/
	if(entity)
	{
		for(size_t i = 0; i < allGameObjectPointers.size(); i++)
		{
			if(allGameObjectPointers[i] == entity)
			{
				allGameObjectPointers.erase(allGameObjectPointers.begin() + i);
				Engine::GUI.requestOverheadRemoval(entity);
				Engine::Graphic.removeFromdrawList(entity);
				//Engine::Window.ListViewer.remove(entity);
				//if(Engine::Window.focus.gameObject == entity)
				//{
				//	Engine::Window.focus.gameObject = 0;
				//	Engine::Window.focus.cleanse();
				//}

				delete entity;
				entity = 0;
				break;
			}
		}
	}
}

//Find the first gameobject pointer inside the gameObjectMap and return the first positive match
GameObject* Game::requestGameObject(std::string name)
{
	for(size_t i = 0; i < allGameObjectPointers.size(); i++)
		if(allGameObjectPointers.at(i)->name == name)
			return allGameObjectPointers.at(i);
	return NULL;
}

const std::vector<GameObject*>* Game::requestAllGameObjecVector() const
{
	return &allGameObjectPointers;
}

void Game::addPhysics(RigidComponent* obj)
{
	if(obj)
		rigids.push_back(obj);
}
void Game::addPhysics(HitboxComponent* obj)
{
	if(obj)
		hitboxes.push_back(obj);
}

void Game::removePhysics(RigidComponent* obj)
{
	if(obj)
		for(size_t i = 0; i < rigids.size(); ++i)
			if(rigids[i] == obj)
			{
				rigids.erase(rigids.begin() + i);
				break;
			}
}
void Game::removePhysics(HitboxComponent* obj)
{
	if(obj)
		for(size_t i = 0; i < hitboxes.size(); ++i)
			if(obj == hitboxes[i])
			{
				hitboxes.erase(hitboxes.begin() + i);
				break;
			}
}
//*/

void Game::addTimedObject(Component::Timer* obj)
{
	if (obj)
		timedObject.push_back(obj);
}
void Game::removeTimedObject(Component::Timer* obj)
{
	if (obj)
		for (size_t i = 0; i < timedObject.size(); i++)
			if (obj == timedObject[i])
			{
				timedObject.erase(timedObject.begin() + i);
				break;
			}
}
#include "Game.h"
#include "Component\GameObject.h"
#include "Tile.h"
#include "Gfx.h"
#include "MessageDefiner.hpp"#include "Engine.hpp"//std::vector<GameObject> allGameObject;
Game::~Game()
{
	for(int i = 0; i < allGameObjectPointers.size(); i++)
	{
		if(allGameObjectPointers[i])
		{
			delete allGameObjectPointers[i];
			allGameObjectPointers[i] = 0;
		}
	}
}

void Game::addGameObject(GameObject* entity)
{
	if (mapOfGameObjects.find(entity) != mapOfGameObjects.end())
	{
		mapOfGameObjects[entity]++;
	}
	else
	{
		mapOfGameObjects.insert(std::pair<GameObject*, int>(entity, 1));
	}
	allGameObjectPointers.push_back(entity);
	Engine::Graphic.insertDrawableObject(entity);
}



void Game::addBackground(Tile* t)
{
	SetGfx()->requestBackground(*t);
}
void Game::addForeground(Tile* t)
{
	SetGfx()->insertDrawableForeground(*t);
}
void Game::requestRemovealForeground(Tile* t)
{
	SetGfx()->removeFromForegroundList(*t);
}



void Game::addGameObject(GameObject* entity,Gfx* editor)
{
	allGameObjectPointers.push_back(entity);
	editor->insertDrawableObject(entity);
}
void Game::addGameObject(std::string name)
{
	//GameObject entity(name);
	/*
	allGameObjectVector.push_back(entity);
	this->allGameObjectPointers.push_back(&allGameObjectVector.at(allGameObjectVector.size() - 1));
	Engine::Graphic.insertDrawableObject(&allGameObjectVector.at(allGameObjectVector.size()-1));
	//*/
}
void Game::requestRemoveal(GameObject* entity)
{
	if (mapOfGameObjects.find(entity) != mapOfGameObjects.end()) {
		mapOfGameObjects[entity]--;
		if (mapOfGameObjects[entity] < 1) {
			SetGfx()->removeFromDrawList(entity);
			mapOfGameObjects.erase(entity);
			for (int i = 0; i < allGameObjectPointers.size(); i++)
			{
				if (allGameObjectPointers[i] == entity)
				{
					allGameObjectPointers.erase(allGameObjectPointers.begin() + i);
					delete entity;
					entity = 0;
					break;
				}
			}		
	for (int i = 0; i < allGameObjectPointers.size(); i++)
	{
		if (allGameObjectPointers[i] == entity)
		{
			allGameObjectPointers.erase(allGameObjectPointers.begin()+i);
			delete entity;
			entity = 0;		
			break;
		}
	}
	else
		; // do nothing
	
}
//Find the first gameobject pointer inside the gameObjectMap and return the first positive match
GameObject* Game::requestGameObject(std::string name)
{
	for(int i = 0; i < allGameObjectPointers.size(); i++)
		if(allGameObjectPointers.at(i)->name == name)
			return allGameObjectPointers.at(i);
	return NULL;
}
const std::vector<GameObject*>* Game::requestAllGameObjecVector() const 
{
	return &allGameObjectPointers;
}

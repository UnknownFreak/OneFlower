#include "Game.h"
#include "Component\GameObject.h"
#include "Component\OverheadComponent.hpp"
#include "Tile.h"
#include "Gfx.h"
#include "GUI/Message.hpp"
#include "Component\RenderComponent.h"
#include "../Engine.hpp"//std::vector<GameObject> allGameObject;

Game::~Game()
{
	//TODO: Use find from algorithm
	for(int i = 0; i < allGameObjectPointers.size(); i++)
	{
		if(allGameObjectPointers[i])
		{
			delete allGameObjectPointers[i];
			allGameObjectPointers[i] = 0;
		}
	}
}
void Game::addMotionObject(GameObject* entity)
{
	motionObjectPointers.push_back(entity);
}

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
	//Engine::Graphic.insertDrawableObject(entity);
#ifdef _DEBUG
	Engine::Window.ListViewer.add(entity);
#endif
}

void Game::addSprite(Tile* t,bool isBackground)
{
	Engine::Graphic.insertDrawableSprite(*t,isBackground);
}
void Game::requestRemovealForeground(Tile* t)
{
	Engine::Graphic.removeFromForegroundList(*t);
}
/*
void Game::addGameObject(GameObject* entity,Gfx* editor)
{
allGameObjectPointers.push_back(entity);
editor->insertDrawableObject(entity);
}
//*/

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
	/*
	if(mapOfGameObjects.find(entity) != mapOfGameObjects.end())
	{
	mapOfGameObjects[entity]--;
	if(mapOfGameObjects[entity] < 1)
	{
	Engine::Graphic.removeFromDrawList(entity);
	mapOfGameObjects.erase(entity);
	for(int i = 0; i < allGameObjectPointers.size(); i++)
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
		for(int i = 0; i < allGameObjectPointers.size(); i++)
		{
			if(allGameObjectPointers[i] == entity)
			{
				allGameObjectPointers.erase(allGameObjectPointers.begin() + i);
				Engine::GUI.requestOverheadRemoval(entity);
				Engine::Graphic.removeFromDrawList(entity);
				Engine::Window.ListViewer.remove(entity);
				if(Engine::Window.focus.gameObject == entity)
				{
					Engine::Window.focus.gameObject = 0;
					Engine::Window.focus.cleanse();
				}

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
	for(int i = 0; i < allGameObjectPointers.size(); i++)
		if(allGameObjectPointers.at(i)->name == name)
			return allGameObjectPointers.at(i);
	return NULL;
}

const std::vector<GameObject*>* Game::requestAllGameObjecVector() const
{
	return &allGameObjectPointers;
}
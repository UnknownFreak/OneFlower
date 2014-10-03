#include "Game.h"
#include "Component\GameObject.h"
#include "RenderHandler.h"
//std::vector<GameObject> allGameObject;
void Game::addGameObject(GameObject* entity)
{
	allGameObjectPointers.push_back(entity);
	SetGfx()->insertDrawableObject(entity);
}
void Game::addGameObject(std::string name)
{
	//GameObject entity(name);
	/*
	allGameObjectVector.push_back(entity);
	this->allGameObjectPointers.push_back(&allGameObjectVector.at(allGameObjectVector.size() - 1));
	SetGfx()->insertDrawableObject(&allGameObjectVector.at(allGameObjectVector.size()-1));
	//*/
}
void Game::requestRemoveal(GameObject* entity)
{
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

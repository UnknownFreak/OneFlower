#include <Windows.h>
#include <list>
#include <math.h>
#include "CustomWindow.h"
#include "Gfx.h"

#include "Game.h"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Component\TransformComponent.hpp"
Gfx gfx;
Gfx::Gfx()
{
	camera.reset(sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(800,600)));

	for(int i = 0; i < 5; i++)
	{
		std::vector<Tile> temp;

		for(int j = 0; j < 5; j++)
		{
			Tile tTemp(i,j);
			tTemp.sprite.setPosition(i*tTemp.sprite.getTextureRect().width,j*tTemp.sprite.getTextureRect().height);
			temp.push_back(tTemp);
		}
		tileList.push_back(temp);
	}
	//*/
}
bool Gfx::loadTexture(std::string name) 
{
	sf::Texture tempTexture;
	//Remove this one day
	std::cout << "Testing";


	if (!tempTexture.loadFromFile(name))
	{
		MessageBox(0, "Error loading this file", name.c_str(), MB_OK);
		return false;
	}	
	loadedTextureMap.insert(loadedTextureMap.end(),std::make_pair(name, tempTexture));
		
	return true;

}
sf::Texture* Gfx::requestTexture(std::string name) 
{
	std::map<std::string, sf::Texture>::iterator it;
	it = loadedTextureMap.find(name);
	if (it != loadedTextureMap.end())
		return &it->second;
	if(loadTexture(name))
		return &loadedTextureMap.find(name)->second;
	return false;
}
void Gfx::insertDrawableObject(GameObject* entityToDraw)
{
	std::map<int, std::vector<GameObject*>>::iterator it;
	int renderID = entityToDraw->GetComponent<RenderComponent>()->renderlayer;



	std::map < int, std::vector<GameObject*>>::iterator endIt;

	endIt = gameObjectDrawList.end();
	it = this->gameObjectDrawList.find(renderID);


	if (it == this->gameObjectDrawList.end())
		gameObjectDrawList.insert(gameObjectDrawList.end(), std::pair<int, std::vector<GameObject*>>(renderID, {entityToDraw}));							//it->second.insert(it->second.end(),entityToDraw);
	else if (it != gameObjectDrawList.end())
	{
		bool temp = false; //Rework this, Somehow: check .end()->first < renderID
		#pragma region EntityToDrawInsertionBetween layers
		for (it = gameObjectDrawList.begin(); it != gameObjectDrawList.end(); it++)
		{
			if (renderID > it->first)
			{
				if (renderID < 1 + it->first)
				{
					gameObjectDrawList.insert
											(	gameObjectDrawList.begin(),
												std::pair<int, std::vector<GameObject*>>(renderID, { entityToDraw })
											);
					temp = true;
					break;
				}
			}
		}
		#pragma endregion
		if(!temp)
			gameObjectDrawList.at(renderID).push_back(entityToDraw);
		
	}
}
void Gfx::Draw()
{
	for (std::map<int, std::vector<GameObject*>>::iterator it = gameObjectDrawList.begin(); it != gameObjectDrawList.end(); it++)
		for (int j = 0; j < it->second.size(); j++)
		{
			RenderComponent* rc = it->second[j]->GetComponent<RenderComponent>();
			TransformComponent* tc = it->second[j]->GetComponent<TransformComponent>();
			rc->sprite.setPosition(tc->position.x,tc->position.y);
			SetWindow()->draw(rc->sprite);
			//SetEditWindow()->draw(it->second[j]->GetComponent<RenderComponent>()->sprite);	
		}
}
void Gfx::DrawBG()
{
	for(int i = 0; this->tileList.size(); i++)
	{
		for(int j = 0; tileList.at(0).size(); j++)
		{

		}
	}
}














//ReadOnly, Returns a const value pointer towards gfx
const Gfx* RequestGfx()
{
	return &gfx;
}
//Returns a value pointer toward gfx
Gfx* SetGfx()
{
	return &gfx;
}
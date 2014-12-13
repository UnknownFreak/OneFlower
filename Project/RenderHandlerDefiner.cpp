#include <Windows.h>
#include <list>
#include <math.h>
#include "Gfx.h"
#include "Game.h"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Component\TransformComponent.hpp"
#include "Component\DialogComponent.hpp"
#include "Engine.hpp"
Gfx gfx;
Gfx::Gfx()
{
	camera.reset(sf::FloatRect(0,0,800,600));
/*	if(!rex.create(camera.getSize().x,camera.getSize().y))
	{
		std::cout << "Error creating Rex";
	}
	/*
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
	
	if(!name.empty())
	{
		std::map<std::string,sf::Texture>::iterator it;
		it = loadedTextureMap.find(name);

		if(it != loadedTextureMap.end())
			return &it->second;
		if(loadTexture(name))
			return &loadedTextureMap.find(name)->second;
		return false;
	}
}
void Gfx::insertDrawableObject(GameObject* entityToDraw)
{
	std::map<int, std::vector<GameObject*>>::iterator it;
	std::map < int,std::vector<GameObject*>>::iterator endIt;
	int renderID = entityToDraw->GetComponent<RenderComponent>()->renderlayer;

	it = this->gameObjectDrawList.find(renderID);
	endIt = gameObjectDrawList.end();

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
void Gfx::removeFromDrawList(GameObject* entityToRemove)
{
	int renderID = entityToRemove->GetComponent<RenderComponent>()->renderlayer;
	for(auto it = gameObjectDrawList.begin(); it != gameObjectDrawList.end(); it++)
	{
		for(int i = 0; i < it->second.size();i++)
		{
			if(it->second[i] == entityToRemove)
			{
				it->second.erase(it->second.begin()+i);
				break;
			}
		}
	}
}
void Gfx::Draw()
{
	DrawBG();
	{
		RenderComponent* rc;
		TransformComponent* tc;
		DialogComponent* dc;
		for(std::map<int,std::vector<GameObject*>>::iterator it = gameObjectDrawList.begin(); it != gameObjectDrawList.end(); it++)
		{
			for(int j = 0; j < it->second.size(); j++)
			{
				rc = it->second[j]->GetComponent<RenderComponent>();
				tc = it->second[j]->GetComponent<TransformComponent>();
				dc = it->second[j]->GetComponent<DialogComponent>();
				// not all gameobjects have dialogs
				if (dc)
				{
					if (dc->open)
						dc->updateLocation();
					if (dc->msg->timer.getElapsedTime().asSeconds() > dc->duration && dc->duration > 0)
						dc->close();

				}
				rc->sprite.setPosition(tc->position.x,tc->position.y);
				Engine::Window.View.draw(rc->sprite); 
				if(rc->sprite.getTexture())
				{
					rc->sprite.setPosition(tc->position.x,tc->position.y);
					rc->sprite.setRotation(tc->rotation.x);
					Engine::Window.View.draw(rc->sprite);
				}
				
			}
		}
	}
	DrawTxt();
}
void Gfx::DrawBG()
{
	backgroundSprite.sprite.setPosition(camera.getCenter().x*1.5f, camera.getCenter().y*1.5f);

	Engine::Window.View.draw(backgroundSprite.sprite);
	for (std::vector<Tile>::iterator it = foregroundSpriteList.begin(); it != foregroundSpriteList.end(); it++)
		Engine::Window.View.draw(it->sprite);
}
void Gfx::DrawTxt()
{
	for (int i = 0; i < msg.size(); i++)
	{
		msg[i]->drawMessage(&Engine::Window.View);
		if (msg[i]->timer.getElapsedTime().asSeconds() > msg[i]->duration && msg[i]->duration > 0)
			removeFromMessageList(msg[i]);
	}
}


void Gfx::insertDrawableMessage(Message* messageToDraw) 
{
	messageToDraw->timer.restart();
	msg.push_back(messageToDraw);
}
void Gfx::removeFromMessageList(Message* messageToRemove, bool dElete)
{
	for (int i = 0; i < msg.size(); i++)
	{
		if (msg[i] == messageToRemove)
		{
			if (dElete)
			{
				msg.erase(msg.begin() + i);
				delete messageToRemove;
				messageToRemove = 0;
				break;
			}
			else
			{
				msg.erase(msg.begin() + i);
				break;
			}
		}
	}
}

void Gfx::insertDrawableSprite(Tile fg, bool isBackground)
{
	if (isBackground)
	{
		backgroundSprite = fg;
		backgroundSprite.setRepeated(true);
		backgroundSprite.sprite.setPosition(backgroundSprite.position.x, backgroundSprite.position.y);

		backgroundSprite.sprite.setTextureRect(sf::IntRect(0, 0,
			backgroundSprite.sprite.getTexture()->getSize().x + backgroundSprite.sizeX,
			backgroundSprite.sprite.getTexture()->getSize().y + backgroundSprite.sizeY));
		backgroundSprite.sprite.setOrigin(backgroundSprite.sprite.getTextureRect().width / 2, backgroundSprite.sprite.getTextureRect().height / 2);
	}
	else
	{
		fg.sprite.setPosition(fg.position.x, fg.position.y);

		fg.sprite.setTextureRect(
			sf::IntRect(0, 0,
			fg.sprite.getTexture()->getSize().x,
			fg.sprite.getTexture()->getSize().y)
			);

		fg.sprite.setOrigin(fg.sprite.getTextureRect().width / 2, fg.sprite.getTextureRect().height / 2);
		foregroundSpriteList.push_back(fg);
	}
}
void Gfx::removeFromForegroundList(Tile fgToRemove)
{
	for (int i = 0; i < foregroundSpriteList.size(); i++)
	{
		if (foregroundSpriteList[i].name == fgToRemove.name)
		{
			foregroundSpriteList.erase(foregroundSpriteList.begin() + i);
			break;
		}
	}
}
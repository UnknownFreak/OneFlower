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
/*
void Gfx::insertShader(sf::Shader sf,std::string t)
{
loadedShaders.insert(std::make_pair(t,sf));
}
sf::Shader* Gfx::reqeustShader(std::string t)
{
if(!t.empty())
{
std::map<std::string,sf::Shader>::iterator it;
it = loadedShaders.find(t);
if(it != loadedShaders.end())
return &it->second;
else
return 0;
}
}
//*/
#include "Component\RigidComponent.hpp"

Gfx::Gfx()
{
	sf::Shader& shader = Engine::Graphic.test;
	//shader.setParameter("texCord",);
	if(!shader.loadFromFile("test.frag",sf::Shader::Fragment))
		MessageBoxA(0,"ErrorLoadingShader","FUUU",0);
	hitbox.setTexture(*requestTexture("HitBox.png"));
}
//*/
bool Gfx::loadTexture(std::string name)
{
	sf::Texture tempTexture;
	if(!tempTexture.loadFromFile("Texture/" + name))
	{
#ifdef _DEBUG
		MessageBox(0,"Error loading this file",name.c_str(),MB_OK);
#endif
		return false;
	}
	loadedTextureMap.insert(loadedTextureMap.end(),std::make_pair(name,tempTexture));

	return true;
}
sf::Texture* Gfx::requestTexture(std::string name)
{
	if (!name.empty())
	{
		std::map<std::string, sf::Texture>::iterator it;
		it = loadedTextureMap.find(name);

		if (it != loadedTextureMap.end())
			return &it->second;

		if (loadTexture(name))
			return &loadedTextureMap.find(name)->second;

		//LOW set propper texturename
		it = loadedTextureMap.find("test.png");
		if (it != loadedTextureMap.end())
			return &it->second;
		loadTexture("test.png");
		return &loadedTextureMap.find("test.png")->second;
	}
}
void Gfx::insertDrawableObject(GameObject* entityToDraw)
{
	std::map<int,std::vector<GameObject*>>::iterator it;
	std::map < int,std::vector<GameObject*>>::iterator endIt;
	int renderID = entityToDraw->GetComponent<RenderComponent>()->renderlayer;

	it = this->gameObjectDrawList.find(renderID);
	endIt = gameObjectDrawList.end();

	if(it == this->gameObjectDrawList.end())
		gameObjectDrawList.insert(gameObjectDrawList.end(),std::pair<int,std::vector<GameObject*>>(renderID,{entityToDraw}));							//it->second.insert(it->second.end(),entityToDraw);
	else if(it != gameObjectDrawList.end())
	{
		bool temp = false; //Rework this, Somehow: check .end()->first < renderID
#pragma region EntityToDrawInsertionBetween layers
		for(it = gameObjectDrawList.begin(); it != gameObjectDrawList.end(); it++)
		{
			if(renderID > it->first)
			{
				if(renderID < 1 + it->first)
				{
					gameObjectDrawList.insert
						(gameObjectDrawList.begin(),
						std::pair<int,std::vector<GameObject*>>(renderID,{entityToDraw})
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
		for(int i = 0; i < it->second.size(); i++)
		{
			if(it->second[i] == entityToRemove)
			{
				it->second.erase(it->second.begin() + i);
				break;
			}
		}
	}
}

void Gfx::Draw()
{
	
	Engine::Graphic.view.render.clear();

	DrawBG();
	{
		RenderComponent* rc;
		TransformComponent* tc;
		DialogComponent* dc;
		//HIGH Fix draw batches to reduce draw calls
		rex.clear();
		for(std::map<int,std::vector<GameObject*>>::iterator it = gameObjectDrawList.begin(); it != gameObjectDrawList.end(); it++)
		{
			for(int j = 0; j < it->second.size(); j++)
			{
				rc = it->second[j]->GetComponent<RenderComponent>();
				tc = it->second[j]->GetComponent<TransformComponent>();
				/*
				dc = it->second[j]->GetComponent<DialogComponent>();
				if(dc)
				{
					if(dc->open)
					{
						dc->updateLocation();
						if(dc->msg->timer.getElapsedTime().asSeconds() > dc->msg->duration && dc->msg->duration > 0)
							dc->close();
					}
				}
				*/
				if(rc->sprite.getTexture())
				{
					rc->sprite.setPosition(tc->position.x,tc->position.y);
					rc->sprite.setRotation(tc->rotation.x);
					rc->sprite.setScale(tc->size.x,tc->size.y);
					rc->updateFrame();
					if(rc->outline)
					{
						sf::Sprite outlineTemp(rc->sprite);

						outlineTemp.setScale((rc->sprite.getTextureRect().width * rc->sprite.getScale().x + rc->outline) / rc->sprite.getTextureRect().width * rc->sprite.getScale().x,(rc->sprite.getTextureRect().height * rc->sprite.getScale().y + rc->outline) / rc->sprite.getTextureRect().height * rc->sprite.getScale().y);
						outlineTemp.setOrigin(rc->outline / 2,rc->outline / 2);
						outlineTemp.setPosition(tc->position.x,tc->position.y);
						test.setParameter("color",1,0,1,1);
						test.setParameter("tex",*rc->sprite.getTexture());

						Engine::Graphic.view.render.draw(outlineTemp,sf::RenderStates(&test));
						//outlineTemp.setColor(sf::Color(255,128,128));
						//	rex.draw(outlineTemp,sf::RenderStates(&test));
					}
					Engine::Graphic.view.render.draw(rc->sprite);

					//rc->sprite.setScale(tc->size.y / (tc->size.x + rc->outline),tc->size.y / (tc->size.y + rc->outline));

					//	rex.draw(rc->sprite);
				}
			}
		}
		//	rex.display();
		//	tex.setTexture(rex.getTexture());
		//Engine::Graphic.view.render.draw(tex);
	}
#ifdef _DEBUG
	if(!Engine::GUI.hideGUI)
	{
		for(size_t i = 0; i < Engine::Physics.hitboxes.size(); i++)
		{
			TransformComponent* tc = Engine::Physics.hitboxes[i]->attachedOn->GetComponent<TransformComponent>();
			hitbox.setPosition(tc->position.x,tc->position.y);

			//TopBar
			hitbox.setTextureRect(sf::IntRect(0,0,Engine::Physics.hitboxes[i]->size.x,2));
			Engine::Graphic.view.render.draw(hitbox);

			double hypno = std::sqrt((
				Engine::Physics.hitboxes[i]->size.x*Engine::Physics.hitboxes[i]->size.x +
				Engine::Physics.hitboxes[i]->size.y*Engine::Physics.hitboxes[i]->size.y
				));
			hitbox.setTextureRect(sf::IntRect(0,0,hypno,2));

			double degree = (std::asin(Engine::Physics.hitboxes[i]->size.y / hypno) * 180) / 3.14159265;

			hitbox.setRotation(degree);
			Engine::Graphic.view.render.draw(hitbox);

			hitbox.setPosition(tc->position.x,tc->position.y + Engine::Physics.hitboxes[i]->size.y);

			hitbox.setRotation(-degree);
			Engine::Graphic.view.render.draw(hitbox);
			hitbox.setRotation(0);

			//BottomBar
			hitbox.setTextureRect(sf::IntRect(0,0,Engine::Physics.hitboxes[i]->size.x,2));
			Engine::Graphic.view.render.draw(hitbox);

			//LeftBar
			hitbox.setPosition(tc->position.x,tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0,0,2,Engine::Physics.hitboxes[i]->size.y));
			Engine::Graphic.view.render.draw(hitbox);

			//RightVBar

			//Engine::Graphic.view.render.draw(hitbox);
			hitbox.setPosition(tc->position.x + Engine::Physics.hitboxes[i]->size.x,tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0,0,2,Engine::Physics.hitboxes[i]->size.y));
			Engine::Graphic.view.render.draw(hitbox);
		}
		for (size_t i = 0; i < Engine::Physics.rigid.size(); i++)
		{
			TransformComponent* tc = Engine::Physics.rigid[i]->attachedOn->GetComponent<TransformComponent>();
			hitbox.setPosition(tc->position.x, tc->position.y);

			//TopBar
			hitbox.setTextureRect(sf::IntRect(0, 0, Engine::Physics.rigid[i]->size.x, 2));
			Engine::Graphic.view.render.draw(hitbox);

			double hypno = std::sqrt((
				Engine::Physics.rigid[i]->size.x*Engine::Physics.rigid[i]->size.x +
				Engine::Physics.rigid[i]->size.y*Engine::Physics.rigid[i]->size.y
				));
			hitbox.setTextureRect(sf::IntRect(0, 0, hypno, 2));

			double degree = (std::asin(Engine::Physics.rigid[i]->size.y / hypno) * 180) / 3.14159265;

			hitbox.setRotation(degree);
			Engine::Graphic.view.render.draw(hitbox);

			hitbox.setPosition(tc->position.x, tc->position.y + Engine::Physics.rigid[i]->size.y);

			hitbox.setRotation(-degree);
			Engine::Graphic.view.render.draw(hitbox);
			hitbox.setRotation(0);

			//BottomBar
			hitbox.setTextureRect(sf::IntRect(0, 0, Engine::Physics.rigid[i]->size.x, 2));
			Engine::Graphic.view.render.draw(hitbox);

			//LeftBar
			hitbox.setPosition(tc->position.x, tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0, 0, 2, Engine::Physics.rigid[i]->size.y));
			Engine::Graphic.view.render.draw(hitbox);

			//RightVBar

			//Engine::Graphic.view.render.draw(hitbox);
			hitbox.setPosition(tc->position.x + Engine::Physics.rigid[i]->size.x, tc->position.y);
			hitbox.setTextureRect(sf::IntRect(0, 0, 2, Engine::Physics.rigid[i]->size.y));
			Engine::Graphic.view.render.draw(hitbox);
		}
	}
#endif

	//*/
	//DrawTxt();

}
void Gfx::DrawBG()
{
	backgroundSprite->sprite.setPosition(Engine::Graphic.view.camera.getCenter().x*1.5f,Engine::Graphic.view.camera.getCenter().y*1.5f);

	Engine::Graphic.view.render.draw(backgroundSprite->sprite);
	for(std::vector<Tile>::iterator it = foregroundSpriteList.begin(); it != foregroundSpriteList.end(); it++)
		Engine::Graphic.view.render.draw(it->sprite);
}
/*
void Gfx::DrawTxt()
{
	for(int i = 0; i < msg.size(); i++)
	{
		msg[i]->drawMessage(&Engine::Graphic.view.render);
		if(msg[i]->timer.getElapsedTime().asSeconds() > msg[i]->duration && msg[i]->duration > 0)
			removeFromMessageList(msg[i]);
	}
}

void Gfx::insertDrawableMessage(Message* messageToDraw)
{
	messageToDraw->timer.restart();
	msg.push_back(messageToDraw);
}
void Gfx::removeFromMessageList(Message* messageToRemove,bool dElete)
{
	for(int i = 0; i < msg.size(); i++)
	{
		if(msg[i] == messageToRemove)
		{
			if(dElete)
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
*/
void Gfx::insertDrawableSprite(Tile& fg,bool isBackground)
{
	if(isBackground)
	{
		backgroundSprite = &fg;
		backgroundSprite->setRepeated(true);
		backgroundSprite->sprite.setPosition(backgroundSprite->position.x,backgroundSprite->position.y);

		backgroundSprite->sprite.setTextureRect(sf::IntRect(0,0,
			backgroundSprite->sprite.getTexture()->getSize().x + backgroundSprite->size.x,
			backgroundSprite->sprite.getTexture()->getSize().y + backgroundSprite->size.x));
		backgroundSprite->sprite.setOrigin(backgroundSprite->sprite.getTextureRect().width / 2,backgroundSprite->sprite.getTextureRect().height / 2);
	}
	else
	{
		fg.sprite.setPosition(fg.position.x,fg.position.y);

		fg.sprite.setTextureRect(
			sf::IntRect(0,0,
			fg.sprite.getTexture()->getSize().x,
			fg.sprite.getTexture()->getSize().y)
			);

		fg.sprite.setOrigin(fg.sprite.getTextureRect().width / 2,fg.sprite.getTextureRect().height / 2);
		foregroundSpriteList.push_back(fg);
	}
}
void Gfx::removeFromForegroundList(Tile& fgToRemove)
{
	for(int i = 0; i < foregroundSpriteList.size(); i++)
	{
		if(foregroundSpriteList[i].name == fgToRemove.name)
		{
			foregroundSpriteList.erase(foregroundSpriteList.begin() + i);
			break;
		}
	}
}
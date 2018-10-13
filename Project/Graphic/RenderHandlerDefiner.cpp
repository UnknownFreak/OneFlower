#include "Gfx.h"
#include <Asset\AssetManagerCore.hpp>
#include <Core\Component\TransformComponent.hpp>
#include <Core\Component\GameObject.h>
#include <Core\EngineModule\EngineModuleManager.hpp>
#include <Core\Logger.hpp>
#include "Component\RenderComponent.h"
#include "Component\DialogComponent.hpp"
#include <SFML\Graphics\RectangleShape.hpp>

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

ResourceType IEngineResource<Gfx>::type = ResourceType::Graphics;

Gfx::Gfx()
{
	backgroundSprite = nullptr;
	/*sf::Shader& shader = Engine::Graphic.test;
	//shader.setParameter("texCord",);
	if(!shader.loadFromFile("test.frag",sf::Shader::Fragment))
		MessageBoxA(0,"ErrorLoadingShader","FUUU",0);*/
}
void Gfx::initDebugTextures()
{
	hitbox.setTexture(Engine::GetModule<Asset::AssetManager>().textureloader.requestTexture("HitBox.png"));
}
//*/
void Gfx::insertDrawableObject(GameObject* entityTodraw)
{
	std::map<int, std::vector<GameObject*>>::iterator it;
	std::map < int, std::vector<GameObject*>>::iterator endIt;
	int renderID = entityTodraw->GetComponent<Component::RenderComponent>()->renderlayer;

	it = this->gameObjectdrawList.find(renderID);
	endIt = gameObjectdrawList.end();

	if (it == this->gameObjectdrawList.end())
		gameObjectdrawList.insert(gameObjectdrawList.end(), std::pair<int, std::vector<GameObject*>>(renderID, { entityTodraw }));							//it->second.insert(it->second.end(),entityTodraw);
	else if (it != gameObjectdrawList.end())
	{
		bool temp = false; //Rework this, Somehow: check .end()->first < renderID
#pragma region EntityTodrawInsertionBetween layers
		for (it = gameObjectdrawList.begin(); it != gameObjectdrawList.end(); it++)
		{
			if (renderID > it->first)
			{
				if (renderID < 1 + it->first)
				{
					gameObjectdrawList.insert
					(gameObjectdrawList.begin(),
						std::pair<int, std::vector<GameObject*>>(renderID, { entityTodraw })
					);
					temp = true;
					break;
				}
			}
		}
#pragma endregion
		if (!temp)
			gameObjectdrawList.at(renderID).push_back(entityTodraw);
	}
}

void Gfx::removeFromdrawList(GameObject* entityToRemove)
{
	if (entityToRemove->GetComponent<Component::RenderComponent>())
	{
		//int renderID = entityToRemove->GetComponent<Component::RenderComponent>()->renderlayer;
		for (auto it = gameObjectdrawList.begin(); it != gameObjectdrawList.end(); it++)
		{
			for (size_t i = 0; i < it->second.size(); i++)
			{
				if (it->second[i] == entityToRemove)
				{
					it->second.erase(it->second.begin() + i);
					break;
				}
			}
		}
	}
}

void Gfx::draw() const
{
	view.render.clear();
	//
	if (bSkipDrawing)
		return;
	drawBG();
	drawObject();
	//drawGrid();
#ifdef _DEBUG
	drawGizmo();
#endif

	//*/
	//drawTxt();
}
void Gfx::drawBG() const
{
	if (backgroundSprite)
	{
		backgroundSprite->sprite.setPosition(view.camera.getCenter().x*1.5f, view.camera.getCenter().y*1.5f);

		view.render.draw(backgroundSprite->sprite);
	}
}

void Gfx::drawObject() const
{
	Component::RenderComponent* rc;
	Component::Transform* tc;
	Component::DialogComponent* dc;
	//HIGH Fix draw batches to reduce draw calls
	//rex.clear();
	for (std::map<int, std::vector<GameObject*>>::const_iterator it = gameObjectdrawList.begin(); it != gameObjectdrawList.end(); it++)
	{
		for (size_t j = 0; j < it->second.size(); j++)
		{
			rc = it->second[j]->GetComponent<Component::RenderComponent>();
			tc = it->second[j]->GetComponent<Component::Transform>();
			
			dc = it->second[j]->GetComponent<Component::DialogComponent>();
			/*if(dc)
			{
			if(dc->open)
			{
			dc->updateLocation();
			if(dc->msg->timer.getElapsedTime().asSeconds() > dc->msg->duration && dc->msg->duration > 0)
			dc->close();
			}
			}
			*/
			if (rc->sprite.getTexture())
			{
				if(rc->model)
				{
					rc->model->setPosition(tc->position);
					rc->updateFrame(30);
					if (rc->outline)
					{
						//sf::Sprite outlineTemp(rc->sprite);
						//
						//outlineTemp.setScale((rc->sprite.getTextureRect().width * rc->sprite.getScale().x + rc->outline) / rc->sprite.getTextureRect().width * rc->sprite.getScale().x, (rc->sprite.getTextureRect().height * rc->sprite.getScale().y + rc->outline) / rc->sprite.getTextureRect().height * rc->sprite.getScale().y);
						//outlineTemp.setOrigin(rc->outline / 2, rc->outline / 2);
						//outlineTemp.setPosition(tc->position.x, tc->position.y);
						////test.setParameter("color", 1, 0, 1, 1);
						////test.setParameter("tex", *rc->sprite.getTexture());
						//
						//Engine::Graphic.view.render.draw(outlineTemp, sf::RenderStates(&test));
						//outlineTemp.setFillColor(sf::Color(255,128,128));
						//	rex.draw(outlineTemp,sf::RenderStates(&test));
					}
					view.render.draw(*rc->model);
					break;
				}
				//rc->sprite.setScale(tc->bounding.size.y / (tc->bounding.size.x + rc->outline),tc->bounding.size.y / (tc->bounding.size.y + rc->outline));
				//	rex.draw(rc->sprite);
			}
		}
	}
	//	rex.display();
	//	tex.setTexture(rex.getTexture());
	//Engine::Graphic.view.render.draw(tex);
}
void Gfx::drawGrid()
{
	sf::RectangleShape box;
	box.setOrigin(sf::Vector2f(0, 0));
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(1);
	box.setSize(sf::Vector2f(16, 16));
	//for (size_t i = 0; i < Engine::game.tiles.size(); i++)
	//{
	//	World::Grid::Tile& tile = Engine::game.tiles.at(i);
	//	//box.setPosition(i%Engine::game.width,(int)i / Engine::game.width);
	//	if (tile.type == World::Grid::Tile::Blank)
	//	{
	//		box.setFillColor(sf::Color::Transparent);
	//	}
	//	else if (tile.type == World::Grid::Tile::Block)
	//	{
	//		box.setFillColor(sf::Color::Cyan);
	//	}
	//	else if (tile.type == World::Grid::Tile::Slope)
	//	{
	//		box.setFillColor(sf::Color::Green);
	//	}
	//	else if (tile.type == World::Grid::Tile::Platform)
	//	{
	//		box.setFillColor(sf::Color::Magenta);
	//		box.setSize(sf::Vector2f(World::Grid::Tile::size, World::Grid::Tile::size / 4));
	//	}
	//	box.setPosition(tile.pos.x * World::Grid::Tile::size, tile.pos.y * World::Grid::Tile::size);
	//	view.render.draw(box);
	//}
}


void Gfx::clearBackground()
{
	backgroundSprite = nullptr;
}

/*
void Gfx::drawTxt()
{
for(size_t i = 0; i < msg.size(); i++)
{
msg[i]->drawMessage(&Engine::Graphic.view.render);
if(msg[i]->timer.getElapsedTime().asSeconds() > msg[i]->duration && msg[i]->duration > 0)
removeFromMessageList(msg[i]);
}
}

void Gfx::insertdrawableMessage(Message* messageTodraw)
{
messageTodraw->timer.restart();
msg.push_back(messageTodraw);
}
void Gfx::removeFromMessageList(Message* messageToRemove,bool dElete)
{
for(size_t i = 0; i < msg.size(); i++)
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
void Gfx::setBackground(BackgroundSprite& bg)
{
	backgroundSprite = &bg;
	backgroundSprite->setRepeated(true);
	backgroundSprite->sprite.setPosition(backgroundSprite->position.x, backgroundSprite->position.y);

	backgroundSprite->sprite.setTextureRect(sf::IntRect(0, 0,
		backgroundSprite->sprite.getTexture()->getSize().x + backgroundSprite->size.x,
		backgroundSprite->sprite.getTexture()->getSize().y + backgroundSprite->size.x));
	backgroundSprite->sprite.setOrigin(backgroundSprite->sprite.getTextureRect().width / 2.f, backgroundSprite->sprite.getTextureRect().height / 2.f);
}

void Gfx::DrawLoadingScreen(BackgroundSprite& loadingScreen, const Core::String& message)
{
	float centerX = view.camera.getCenter().x;
	float centerY = view.camera.getCenter().y;
	float sizeX = view.camera.getSize().x;
	float sizeY = view.camera.getSize().y;
	float width = view.camera.getViewport().width;
	float height = view.camera.getViewport().height;

	const sf::Texture* ptr = loadingScreen.sprite.getTexture();
	if (ptr)
	{

		loadingScreen.setPosition(centerX - (sizeX*width / 2.f), centerY - (sizeY*height / 2.f));

		loadingScreen.sprite.setScale(sizeX / (float)loadingScreen.sprite.getTexture()->getSize().x,
			sizeY / (float)loadingScreen.sprite.getTexture()->getSize().y);

		view.render.draw(loadingScreen.sprite);
	}
	else
		Engine::GetModule<OneLogger>().Error("Loading screen texture pointer was NULL", __FILE__, __LINE__);

	//GUI::Message msg(*Engine::Graphic.font.requestFont("arial.ttf"));

	//msg = message;
	//msg.setPosition(centerX - (sizeX*width / 2.f), centerY - (sizeY*height / 2.f));
	//msg.setFillColor(sf::Color(255, 255, 255));
	//msg.draw();
//		Engine::World.getLoadingScreenProgressBar().draw();
	view.render.display();
}

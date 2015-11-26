#ifndef RenderHandler_H
#define RenderHandler_H
#include <SFML\Graphics\Texture.hpp>
#include <map>
#include <vector>
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "Game\Tile.h"
#include "Game\GUI\Text\Font.hpp"
#include "Game/GameView.hpp"
class Tile;
class GameObject;
class Message;
class Gfx
{
public:
	GameView view;
	Gfx();
	GUI::Text::Font font;
	std::vector<Message *> msg;

#pragma region Texture Related Functions
	//Load a picture file into a Texture and not a sprite
	bool loadTexture(std::string locatonOfTheTexture);

	//Return a pointer towards
	sf::Texture* requestTexture(std::string name);

	//request removal of texture if its not in use
	void requestRemovalOfTexture(std::string name);
#pragma endregion
	/*
	void insertShader(sf::Shader sf,std::string);
	sf::Shader* reqeustShader(std::string t);
	//*/
	void insertDrawableObject(GameObject* drawableEntity);
	void removeFromDrawList(GameObject* objectToRemove);
	std::vector<std::vector<Tile*>> tileList;

	//Draw all Game object with RenderComponent attached to it
	void Draw();
	void DrawBG();
	std::vector<GameObject*> selectedDrawList;
	std::vector<Tile> foregroundSpriteList;
	sf::RenderTexture rex;
	sf::Sprite tex;
	void insertDrawableSprite(Tile& fg,bool isBackground);
	void removeFromForegroundList(Tile& fgToRemove);
	/*
	void insertDrawableMessage(Message* msg);
	void removeFromMessageList(Message* msg,bool dElete = true);
	void DrawTxt();
	*/
	sf::Shader test;
	sf::Sprite hitbox;
private:
	//Map with all texture, key value is the name of the texture
	std::map<std::string,sf::Texture> loadedTextureMap;
	std::map<int,std::vector<GameObject*>> gameObjectDrawList;
	Tile* backgroundSprite;
};
#endif	
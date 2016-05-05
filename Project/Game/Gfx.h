#ifndef RenderHandler_H
#define RenderHandler_H
#include <SFML\Graphics\Texture.hpp>
#include <map>
#include <vector>
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "Tile.h"
#include "GUI/Text/Font.hpp"
#include "GameView.hpp"
class Tile;
class GameObject;
class Message;
class Gfx
{
public:
	GameView view;
	Gfx();
	Font font;
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
	void insertdrawableObject(GameObject* drawableEntity);
	void removeFromdrawList(GameObject* objectToRemove);
	std::vector<std::vector<Tile*>> tileList;

	//draw all Game object with RenderComponent attached to it
	void draw();
	void drawBG();
	void drawObject();
	void drawGrid();
#ifdef _DEBUG
	void drawGizmo();
#endif
	std::vector<GameObject*> selecteddrawList;
	std::vector<Tile> foregroundSpriteList;
	sf::RenderTexture rex;
	sf::Sprite tex;
	void insertdrawableSprite(Tile& fg,bool isBackground);
	void removeFromForegroundList(Tile& fgToRemove);
	/*
	void insertdrawableMessage(Message* msg);
	void removeFromMessageList(Message* msg,bool dElete = true);
	void drawTxt();
	*/
	sf::Shader test;
	sf::Sprite hitbox;
private:
	//Map with all texture, key value is the name of the texture
	std::map<std::string,sf::Texture> loadedTextureMap;
	std::map<int,std::vector<GameObject*>> gameObjectdrawList;
	Tile* backgroundSprite;
};
#endif	
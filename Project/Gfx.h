#ifndef RenderHandler_H
#define RenderHandler_H
#include <SFML\Graphics\Texture.hpp>
#include <map>
#include <vector>
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "Tile.h"
#include "FontDefiner.hpp"
class GameObject;
class Message;
class Gfx
{
public:
    Gfx();
    #pragma region Texture Related Functions
    //Load a picture file into a Texture and not a sprite
    bool loadTexture(std::string locatonOfTheTexture);
    
    //Return a pointer towards
    sf::Texture* requestTexture(std::string name) ;

    //request removal of texture if its not in use
    void requestRemovalOfTexture(std::string name);
    #pragma endregion

    void insertDrawableObject(GameObject* drawableEntity);	
	void removeFromDrawList(GameObject* objectToRemove);
    sf::View camera; 
    std::vector<std::vector<Tile*>> tileList;

    //Draw all Game object with RenderComponent attached to it
    void Draw();
    void DrawBG();
    std::vector<GameObject*> selectedDrawList;
	std::vector<Tile> foregroundSpriteList;
    //sf::RenderTexture rex;

	void requestBackground(Tile bg);
	void insertDrawableForeground(Tile fg);
	void removeFromForegroundList(Tile fgToRemove);
	void moveBackground(int x, int y,float panSpeed);

	Font font;
	std::vector<Message *> msg;
	void insertDrawableMessage(Message* msg);
	void removeFromMessageList(Message* msg);
	void DrawTxt();
private:
    //Map with all texture, key value is the name of the texture
    std::map<std::string,sf::Texture> loadedTextureMap;
    std::map<int,std::vector<GameObject*>> gameObjectDrawList;
	Tile backgroundSprite;
};
//ReadOnly
const Gfx* RequestGfx();
//Returns a pointer value towards 
Gfx* SetGfx();

#endif	
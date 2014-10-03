#ifndef RenderHandler_H
#define RenderHandler_H
#include <SFML\Graphics\Texture.hpp>
#include <map>
#include <vector>
class GameObject;
class Gfx
{
public:

	#pragma region Texture Related Functions
	//Load a picture file into a Texture and not a sprite
	bool loadTexture(std::string locatonOfTheTexture);
	
	//Return a pointer towards
	sf::Texture* requestTexture(std::string name) ;
	//request removal of texture if its not in use
	void requestRemovalOfTexture(std::string name);
	#pragma endregion

	void insertDrawableObject(GameObject* drawableEntity);	


	//Draw all Game object with RenderComponent attached to it
	void Draw();
	std::vector<GameObject*> selectedDrawList;


private:
	//Map with all texture, key value is the name of the texture
	std::map<std::string,sf::Texture> loadedTextureMap;
	std::map<int,std::vector<GameObject*>> gameObjectDrawList;

};
//ReadOnly
const Gfx* RequestGfx();
//Returns a pointer value towards 
Gfx* SetGfx();

#endif	
#ifndef RenderHandler_H
#define RenderHandler_H
#include <map>
#include <vector>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Shader.hpp>
#include "BackgroundSprite\BackgroundSprite.hpp"
#include "RenderView.hpp"
#include <AssetManager/SpriteRef.hpp>
#include <Core\IEngineResource\IEngineResource.hpp>

class GameObject;
//class GUI::::Message;
class Gfx : public IEngineResource<Gfx>
{

public:
	
	
	mutable RenderView view;
	Gfx();
	void initDebugTextures();
	/*
	void insertShader(sf::Shader sf,std::string);
	sf::Shader* reqeustShader(std::string t);
	//*/
	void insertDrawableObject(GameObject* drawableEntity);
	void removeFromdrawList(GameObject* objectToRemove);
	std::vector<std::vector<BackgroundSprite*>> tileList;

	//Draw all Game object with RenderComponent attached to it
	void DrawLoadingScreen(BackgroundSprite& loadingscreen, Core::String& info);
	//draw all Game object with RenderComponent attached to it
	void draw() const;
	void drawBG() const;
	void drawObject() const;
	void drawGrid();

	bool bSkipDrawing = false;

#ifdef _DEBUG
	void drawGizmo() const;
	bool drawHitboxes = true;
#endif
	std::vector<GameObject*> selectedDrawList;
	std::vector<BackgroundSprite> foregroundSpriteList;
	sf::Sprite tex;
	void clearBackground();
	void setBackground(BackgroundSprite& bg);
	void removeFromForegroundList(BackgroundSprite& fgToRemove);
	/*
	void insertdrawableMessage(Message* msg);
	void removeFromMessageList(Message* msg,bool dElete = true);
	void drawTxt();
	*/
	sf::Shader test;

	mutable SpriteRef hitbox;

	const ResourceType& getType()
	{
		return type;
	}

private:
	//Map with all texture, key value is the name of the texture
	std::map<int, std::vector<GameObject*>> gameObjectdrawList;
	BackgroundSprite* backgroundSprite;
};
#endif	
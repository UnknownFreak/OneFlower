#ifndef GUI_HPP
#define GUI_HPP
#include "Tile.h"
#include "Text\Message.hpp"
#include<vector>
#include<SFML\Graphics\Text.hpp>
class GameObject;

class GraphicalUserInterface
{
public:


	Tile mouseAim;
	Tile mouseSlotRight;
	Tile mouseSlotLeft;

	sf::Text t;
	Message overhead;
	GameObject* ObjectToFollow;
	//Todo change to Gameobject??
	std::vector<GameObject*> ActionSlot;
	//std::vector<GameObject*> gameobjects;
	//std::vector<Message*> messages;


	GraphicalUserInterface();
	~GraphicalUserInterface();
	void updateMouse();
	void Draw();
	void setMouseVisible();
	void setActiveSkill(std::string buttonName);
	void setObjectToFollow(GameObject* follow);
private:
	void setIconLocation();
	const float* x;
	const float* xSize;
	const float* y;
	const float* ySize;
};


#endif // ! GUI_HPP
#ifndef GUI_HPP
#define GUI_HPP

#include "Component\HitboxComponent.hpp"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include "Component\TransformComponent.hpp"
#include "Component\OverheadComponent.hpp"
#include "ButtonObject.hpp"

#include "Tile.h"
#include "Text\Message.hpp"
#include<vector>
#include<SFML\Graphics\Text.hpp>

class DialogComponent;
class GraphicalUserInterface
{
public:

	bool hideGUI;
	bool isMouseVisible;
	bool showOverhead;
	bool showDialog;

	Tile mouseAim;


	Button mouseSlotRight;
	Button mouseSlotLeft;

	sf::Text t;
	std::vector<OverheadComponent*> overhead;
	std::vector<DialogComponent*> dialogs;
	
	std::vector<Button*> ActionSlot;
	//std::vector<Message*> messages;

	GraphicalUserInterface();
	~GraphicalUserInterface();
	void updateMouseIcon();
	void Draw();
	void showHideMouse();
	void showHideDialogs();
	void setActiveSkill(std::string buttonName);

	void setCursor(std::string name);

	void showHideOverhead();
	void showHideGUI();
	void addOverhead(GameObject* over);
	void requestOverheadRemoval(GameObject* go);
	void addDialog(DialogComponent &dcp);
	void removeDialog(DialogComponent &dcp);
private:

	void initialize();

	void setIconLocation();
	Vector2 offset;
};

#endif // ! GUI_HPP
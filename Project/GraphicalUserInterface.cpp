#include "GraphicalUserInterface.hpp"
#include "Engine.hpp"
#include <SFML\Window\Mouse.hpp>

#include <Windows.h>


GraphicalUserInterface::GraphicalUserInterface() : offset(0, 0), hideGUI(true), showOverhead(true), isMouseVisible(true), mouseSlotRight("ButtonTest.png"), mouseSlotLeft("ButtonTest.png")
{
	
	// Mouse
	setCursor("Aim.png");
	initialize();
}
GraphicalUserInterface::~GraphicalUserInterface()
{
	
}
void GraphicalUserInterface::updateMouseIcon()
{
	mouseAim.setPosition((float)(Engine::mouse.pos.x - 15) ,(float) (Engine::mouse.pos.y - 15 ));
}

void GraphicalUserInterface::setIconLocation()
{
	mouseSlotLeft.setPosition(
		270 +Engine::mouse.offset.x,
		30 + Engine::mouse.offset.y);
	mouseSlotRight.setPosition(
		400 + Engine::mouse.offset.x,
		30 + Engine::mouse.offset.y);
}

void GraphicalUserInterface::setActiveSkill(std::string buttonName)
{
	//Todo: check type of skill and set on left or right mouse
	if (buttonName == "ActionBar0")
	{
		mouseSlotLeft.icon = ActionSlot[0]->icon;
	}
	else if (buttonName == "ActionBar1")
	{
		mouseSlotLeft.icon = ActionSlot[1]->icon;
	}
	else if (buttonName == "ActionBar2")
	{
		mouseSlotLeft.icon = ActionSlot[2]->icon;
	}
	else if (buttonName == "ActionBar3")
	{
		mouseSlotLeft.icon = ActionSlot[3]->icon;
	}
}

void GraphicalUserInterface::addOverhead(GameObject* entity)
{
	if (entity->GetComponent<OverheadComponent>())
		overhead.push_back(entity->GetComponent<OverheadComponent>());
}

void GraphicalUserInterface::requestOverheadRemoval(GameObject* entity)
{
	OverheadComponent* tmp = entity->GetComponent<OverheadComponent>();
	if (tmp)
		for (std::vector<OverheadComponent*>::iterator it = overhead.begin(); it != overhead.end(); ++it)
			if (tmp == *it)
			{
				overhead.erase(it);
				break;
			}
}

void GraphicalUserInterface::setCursor(std::string name)
{
	mouseAim.sprite.setTexture(*Engine::Graphic.requestTexture(name), true);
}

void GraphicalUserInterface::initialize()
{
	mouseSlotRight.setPosition(270, 30);
	mouseSlotLeft.setPosition(400, 30);

	// buttons
	for (size_t i = 0; i < 4; i++)
	{
		Button* tmp = new Button();
		tmp->name = "ActionBar" + std::to_string(i);
		tmp->setIcon("buttonTest.png");
		tmp->setPosition(40 + 128 * i,500);
		ActionSlot.push_back(tmp);
	}
	ActionSlot[0]->setIcon("testTarget.png");
}


void GraphicalUserInterface::showHideMouse()
{
	if (isMouseVisible)
		isMouseVisible = false;
	else
		isMouseVisible = true;
}

void GraphicalUserInterface::showHideGUI()
{
	if (Engine::GUI.hideGUI)
		Engine::GUI.hideGUI = false;
	else
		Engine::GUI.hideGUI = true;
}
void GraphicalUserInterface::showHideOverhead()
{
	if (Engine::GUI.hideGUI)
		Engine::GUI.hideGUI = false;
	else
		Engine::GUI.hideGUI = true;
}
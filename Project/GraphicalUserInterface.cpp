#include "GraphicalUserInterface.hpp"
#include "Engine.hpp"
#include <SFML\Window\Mouse.hpp>
#include "Component\HitboxComponent.hpp"
#include "Component\GameObject.h"
#include "Component\RenderComponent.h"
#include "Component\TransformComponent.hpp"
#include <Windows.h>
GraphicalUserInterface::GraphicalUserInterface() :
overhead(*Engine::Graphic.font.requestFont("Arial.ttf")), mouseAim(), mouseSlotRight(), mouseSlotLeft()
{
	// Mouse
	mouseAim.sprite.setTexture(*Engine::Graphic.requestTexture("Aim.png"),true);
	mouseAim.setRepeated(false);
	mouseAim.name = "AimStuff";

	//Mousebar
	mouseSlotRight.sprite.setTexture(*Engine::Graphic.requestTexture("MouseIconTest.png"), true);
	mouseSlotRight.name = "Rightmousebar";
	mouseSlotRight.setPosition(270, 30);
	mouseSlotLeft.sprite.setTexture(*Engine::Graphic.requestTexture("MouseIconTest.png"), true);
	mouseSlotLeft.name = "Leftmousebar";
	mouseSlotLeft.setPosition(400, 30);


	x = &Engine::Graphic.camera.getCenter().x;
	xSize = &Engine::Graphic.camera.getSize().x;
	y = &Engine::Graphic.camera.getCenter().y;
	ySize = &Engine::Graphic.camera.getSize().y;
	// buttons
	for (int i = 0; i < 4; i++)
	{
		GameObject* tmp = new GameObject();
		tmp->name = "ActionBar" + std::to_string(i);
		tmp->AddComponent(new RenderComponent("ButtonTest.png"));
		tmp->GetComponent<RenderComponent>()->sprite.setColor(sf::Color(255 - (63 * i), 255 - (63 * i), 255 - (63 * i)));
		tmp->GetComponent<TransformComponent>()->position.x = 40 + 128 * i;
		tmp->GetComponent<TransformComponent>()->position.x = 500;
		tmp->AddComponent(new HitboxComponent());
		ActionSlot.push_back(tmp);
	}

	// Overhead
	
	overhead.text.setString("Some amazing text");
	overhead.setSize(25);
	overhead.setPosition(*x - *xSize / 2, *y - *ySize / 2);
	overhead.setColor(sf::Color(255, 255, 255));
}
void GraphicalUserInterface::Draw()
{
	setIconLocation();
	Engine::Window.View.draw(mouseSlotLeft.sprite);
	Engine::Window.View.draw(mouseSlotRight.sprite);
	for (size_t i = 0; i < ActionSlot.size(); i++)
	{	
		ActionSlot[i]->GetComponent<TransformComponent>()->position.x = 40 + 128 * i + *x - *xSize / 2;
		ActionSlot[i]->GetComponent<TransformComponent>()->position.y = 500 + *y - *ySize / 2;
		ActionSlot[i]->GetComponent<RenderComponent>()->sprite.setPosition(
			40 + 128 * i + *x - *xSize / 2,
			500 + *y - *ySize / 2);
			
		Engine::Window.View.draw(ActionSlot[i]->GetComponent<RenderComponent>()->sprite);
	}
	Engine::Window.View.draw(overhead.text);
	Engine::Window.View.draw(mouseAim.sprite);
}
GraphicalUserInterface::~GraphicalUserInterface()
{
	
}
void GraphicalUserInterface::updateMouse()
{
	mouseAim.setPosition(
		sf::Mouse::getPosition(Engine::Window.View).x -15 + *x - *xSize / 2,
		sf::Mouse::getPosition(Engine::Window.View).y - 15 + *y- *ySize/2
		);
}

void GraphicalUserInterface::setIconLocation()
{
	mouseSlotLeft.setPosition(
		270 + *x - *xSize/2,
		30 + *y - *ySize/2
		);
	mouseSlotRight.setPosition(
		400 + *x - *xSize/2,
		30 + *y - *ySize/2
		);
		//*/
	if (ObjectToFollow)
		overhead.setPosition(
		(float)(ObjectToFollow->GetComponent<TransformComponent>()->position.x - ObjectToFollow->GetComponent<RenderComponent>()->size.x / 3),
		(float)(ObjectToFollow->GetComponent<TransformComponent>()->position.y - ObjectToFollow->GetComponent<RenderComponent>()->size.y / 2));
}

void GraphicalUserInterface::setActiveSkill(std::string buttonName)
{
	//Todo: check type of skill and set on left or right mouse
	if (buttonName == "ActionBar0")
		mouseSlotLeft.sprite = ActionSlot[0]->GetComponent<RenderComponent>()->sprite;
	else if (buttonName == "ActionBar1")
		mouseSlotLeft.sprite = ActionSlot[1]->GetComponent<RenderComponent>()->sprite;
	else if (buttonName == "ActionBar2")
		mouseSlotLeft.sprite = ActionSlot[2]->GetComponent<RenderComponent>()->sprite;
	else if (buttonName == "ActionBar3")
		mouseSlotLeft.sprite = ActionSlot[3]->GetComponent<RenderComponent>()->sprite;
}

void GraphicalUserInterface::setObjectToFollow(GameObject* follow)
{
	ObjectToFollow = follow;
	overhead.setPosition(
		float(ObjectToFollow->GetComponent<TransformComponent>()->position.x-ObjectToFollow->GetComponent<RenderComponent>()->size.x/2),
		float(ObjectToFollow->GetComponent<TransformComponent>()->position.y));
}
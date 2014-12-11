#include "DialogComponent.hpp"
#include "../Gfx.h"
#include "../Engine.hpp"
#include "../Game.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.hpp"

std::string IBaseComponent<DialogComponent>::componentName = "DialogComponent";
const unsigned int IBaseComponent<DialogComponent>::typeID = 2222;


DialogComponent::~DialogComponent()
{
	if (go)
		Engine::game.requestRemoveal(go);
	go = 0;
	delete rex;
}

DialogComponent::DialogComponent(float dur)
{
	
	rex = new sf::RenderTexture();
	rex->create(128, 64);
	sprt.setTexture(*Engine::Graphic.requestTexture("test.png"));
	dialogTexture = "test.png";
	fontName = "arial.ttf";
	duration = dur;
	open = false;
}

void DialogComponent::show()
{
	if (!open)
	{
		sprt.setTexture(*Engine::Graphic.requestTexture("TestDialogChat.png"));
		msg.text.setFont(*Engine::Graphic.font.requestFont(fontName));
		msg.duration = duration;
		msg.setColor(sf::Color::Black);
		msg.setSize(12);
		msg = "Testing a dialog\n testing line two";
		msg.setPosition(10, 3);
		msg.timer.restart();
		
		

		go = new GameObject("TestDialog");
		go->AddComponent(new RenderComponent());
		go->GetComponent<RenderComponent>()->sprite.setTexture(rex->getTexture(),true);
		go->GetComponent<RenderComponent>()->renderlayer = 5;
		/*
			set coordinates relative to the object interracted to

		//*/
		Engine::game.addGameObject(go);
		rex->clear(sf::Color::Transparent);
		rex->draw(sprt);
		rex->draw(msg.text);
		rex->display();
		
		open = true;
	}
}
void DialogComponent::close()
{
	if (open)
	{
		Engine::game.requestRemoveal(go);

		go = 0;
		open = false;
	}
}


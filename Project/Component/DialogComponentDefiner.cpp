#include "DialogComponent.hpp"
#include "../Gfx.h"
#include "../Engine.hpp"
#include "../Game.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.hpp"


const unsigned int IBaseComponent<DialogComponent>::typeID = 2222;
std::string IBaseComponent<DialogComponent>::componentName = "DialogComponent";

DialogComponent::DialogComponent()
{
	REGISTER_EDITOR_VARIABLE(int, offsetX, OffsetX);
	REGISTER_EDITOR_VARIABLE(int, offsetY, OffsetY);
	REGISTER_EDITOR_VARIABLE(int, textOffsetX, TextOffsetX);
	REGISTER_EDITOR_VARIABLE(int, textOffsetY, TextOffsetY);
	REGISTER_EDITOR_VARIABLE(float, duration, Duration);
	REGISTER_EDITOR_VARIABLE(std::string, dialogTexture, Texture);
	REGISTER_EDITOR_VARIABLE(std::string, fontName, FontName);
	REGISTER_EDITOR_VARIABLE(std::string, dialogMessage, Text);
	
	rex = new sf::RenderTexture();
	rex->create(128, 64);
	msg = new FloatingText();
	dialogTexture = "test.png";
	fontName = "arial.ttf";
	dialogMessage = "NotSet";
	duration = -1;
	offsetX = 0;
	offsetY = 0;
	textOffsetX = 0;
	textOffsetY = 0;
	open = false;
	dCreated = false;
}

DialogComponent::DialogComponent(float dur)
{
	REGISTER_EDITOR_VARIABLE(int, offsetX, OffsetX);
	REGISTER_EDITOR_VARIABLE(int, offsetY, OffsetY);
	REGISTER_EDITOR_VARIABLE(int, textOffsetX, TextOffsetX);
	REGISTER_EDITOR_VARIABLE(int, textOffsetY, TextOffsetY);
	REGISTER_EDITOR_VARIABLE(float, duration, ShowDuration);
	REGISTER_EDITOR_VARIABLE(std::string, dialogTexture, Texture);
	REGISTER_EDITOR_VARIABLE(std::string, fontName, FontName);
	REGISTER_EDITOR_VARIABLE(std::string, dialogMessage, Text);

	rex = new sf::RenderTexture();
	rex->create(128, 64);
	msg = new FloatingText();
	dialogTexture = "test.png";
	fontName = "arial.ttf";
	dialogMessage = "NotSet";
	duration = dur;
	offsetX = 0;
	offsetY = 0;
	textOffsetX = 0;
	textOffsetY = 0;
	open = false;
	dCreated = false;
}
DialogComponent::DialogComponent(const DialogComponent &diag)
{
	REGISTER_EDITOR_VARIABLE(int, offsetX, OffsetX);
	REGISTER_EDITOR_VARIABLE(int, offsetY, OffsetY);
	REGISTER_EDITOR_VARIABLE(int, textOffsetX, TextOffsetX);
	REGISTER_EDITOR_VARIABLE(int, textOffsetY, TextOffsetY);
	REGISTER_EDITOR_VARIABLE(float, duration, ShowDuration);
	REGISTER_EDITOR_VARIABLE(std::string, dialogTexture, Texture);
	REGISTER_EDITOR_VARIABLE(std::string, fontName, FontName);
	REGISTER_EDITOR_VARIABLE(std::string, dialogMessage, Text);

	
	rex = new sf::RenderTexture();
	rex->create(128, 64);
	msg = new FloatingText();
	dialogTexture = diag.dialogTexture;
	fontName = diag.fontName;
	duration = diag.duration;
	dialogMessage = diag.dialogMessage;
	offsetX = diag.offsetX;
	offsetY = diag.offsetY;
	textOffsetX = diag.textOffsetX;
	textOffsetY = diag.textOffsetY;

	open = false;
	dCreated = false;
}

DialogComponent::~DialogComponent()
{
	delete msg;
	msg = nullptr;
	delete rex;
}

void DialogComponent::updateLocation()
{
	msg->setOffset(textOffsetX, textOffsetY);
	//HIGH Fix this with floor and research more
	msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - offsetX + .51f, this->attachedOn->GetComponent<TransformComponent>()->position.y - offsetY + .51f);
}
//TODO Remove either this one or the other updateLocation
void DialogComponent::createDialog(bool b)
{
	sprt.setTexture(*Engine::Graphic.requestTexture(dialogTexture));
	rex->draw(sprt);
	msg->setFont(Engine::Graphic.font.requestFont(fontName));
	msg->duration = -1;
	msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - offsetX, this->attachedOn->GetComponent<TransformComponent>()->position.y - offsetY);
	msg->setColor(sf::Color::Black);
	msg->setSize(12);
	*msg = dialogMessage;
	rex->draw(msg->text);
	rex->display();
	msg->iconSprite.setTexture(rex->getTexture());
	dCreated = true;
}
void DialogComponent::createDialog()
{	
	msg->setIcon(dialogTexture);
	msg->setFont(Engine::Graphic.font.requestFont(fontName));
	msg->duration = -1;
	msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - offsetX, this->attachedOn->GetComponent<TransformComponent>()->position.y - offsetY);
	msg->setColor(sf::Color::Black);
	msg->setSize(12);
	*msg = dialogMessage;
	
	dCreated = true;
}
void DialogComponent::show()
{
	if (!open)
	{
		msg->timer.restart();
		/*
			set coordinates relative to the object interracted to

		//*/
		//TODO: Fix this cause this apparently use alot of resources depedning on machine
		if (!dCreated)
			createDialog();
		Engine::Graphic.insertDrawableMessage(msg);
		open = true;
	}
}
void DialogComponent::close()
{
	if (open)
	{
		Engine::Graphic.removeFromMessageList(msg,false);
		open = false;
	}
}


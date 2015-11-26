#include "DialogComponent.hpp"
#include "../Gfx.h"
#include "../../Engine.hpp"
#include "../Game.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.hpp"
const unsigned int IBaseComponent<DialogComponent>::typeID = 1004;
std::string IBaseComponent<DialogComponent>::componentName = "DialogComponent";

DialogComponent::DialogComponent():
fontName("arial.ttf"),
dialogMessage("NotSet"),
position(0,0),
open(false),dCreated(false),msg(new GUI::Text::FloatingText())
{
	//rex = new sf::RenderTexture();
	//rex->create(128, 64);
	msg->iconName = "test.png";
}

DialogComponent::DialogComponent(double dur):
fontName("arial.ttf"),
dialogMessage("NotSet"),
position(0,0),
open(false), dCreated(false), msg(new GUI::Text::FloatingText())
{
	//rex = new sf::RenderTexture();
	//rex->create(128, 64);
	msg->iconName = "test.png";
	msg->duration = dur;
}
DialogComponent::DialogComponent(const DialogComponent &diag):
fontName("arial.ttf"),
dialogMessage(diag.dialogMessage),
position(diag.position),
open(false), dCreated(false), msg(new GUI::Text::FloatingText(*diag.msg))
{
	//rex = new sf::RenderTexture();
	//rex->create(128, 64);
}

DialogComponent::~DialogComponent()
{
	delete msg;
	msg = nullptr;
	//delete rex;
}

void DialogComponent::attachOn(GameObject* go)
{
	DialogComponent::BaseComponent::attachOn(go);
	REGISTER_EDITOR_VARIABLE(Vector2,position,Position);
	REGISTER_EDITOR_VARIABLE(Vector2,msg->offset,TextOffset);
	REGISTER_EDITOR_VARIABLE(double,msg->duration,ShowDuration);
	REGISTER_EDITOR_VARIABLE(std::string,fontName,FontName);
	REGISTER_EDITOR_VARIABLE(std::string,dialogMessage,Text);
	REGISTER_EDITOR_VARIABLE(std::string,msg->iconName,Texture);
	REGISTER_EDITOR_VARIABLE(bool,msg->drawIcon,DrawBackgroundImage);
}
void DialogComponent::updateLocation()
{
	//HIGH Fix this with floor and research more

	if(!msg)
		MessageBox(Engine::Window.hWnd,"Not suppoed to happen!","Dafak",NULL);
	else
		msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - position.x + .51f,this->attachedOn->GetComponent<TransformComponent>()->position.y - position.y + .51f);
	msg->setPosition(attachedOn->GetComponent<TransformComponent>()->position.x - position.x + .51f,attachedOn->GetComponent<TransformComponent>()->position.y - position.y + .51f);
}
//TODO Remove either this one or the other createDialog
void DialogComponent::createDialog(bool b)
{
	//sprt.setTexture(*Engine::Graphic.requestTexture(msg->iconName));
	//rex->draw(sprt);
	msg->setFont(Engine::Graphic.font.requestFont(fontName));
	//msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - position.x, this->attachedOn->GetComponent<TransformComponent>()->position.y - position.y);
	updateLocation();
	msg->setColor(msg->color);
	msg->setSize(12);
	*msg = dialogMessage;
	//rex->draw(msg->text);
	//rex->display();
	//msg->iconSprite.setTexture(rex->getTexture());
	dCreated = true;
}
void DialogComponent::createDialog()
{
	tryLoadTextureAndFont();

	msg->setColor(msg->color);
	msg->setSize(12);
	*msg = dialogMessage;

	dCreated = true;
}
void DialogComponent::show()
{
	updateLocation();
	if(!open)
	{
		msg->timer.restart();

		//TODO: Fix this cause this apparently use alot of resources depedning on machine
		if(!dCreated)
			createDialog();
		Engine::GUI.addDialog(*this);
		//Engine::Graphic.insertDrawableMessage(msg);
		open = true;
	}
}
void DialogComponent::close()
{
	if(open)
	{
		Engine::GUI.removeDialog(*this);
		//Engine::Graphic.removeFromMessageList(msg,false);
		open = false;
	}
}
bool DialogComponent::updateFromEditor()
{
	tryLoadTextureAndFont();
	updateLocation();
	msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - position.y,this->attachedOn->GetComponent<TransformComponent>()->position.y - position.y);
	*msg = dialogMessage;

	return true;
}

void DialogComponent::tryLoadTextureAndFont()
{
#ifdef _DEBUG
	try
	{
#endif
		msg->setIcon(msg->iconName);
		msg->setFont(Engine::Graphic.font.requestFont(fontName));

#ifdef _DEBUG
	}
	catch (GUI::Text::MissingIconException ex)
	{
		MessageBox(Engine::Window.hWnd,"Missing Dialog Texture","Error:MissingDialogTexture",NULL);

		msg->iconSprite.setTexture(*ex.what());
	}
	catch (GUI::Text::MissingFontException ex)
	{
		MessageBox(Engine::Window.hWnd,"Missing Dialog Font","Error:MissingDialogFont",NULL);

		msg->setFont(ex.what());
	}
#endif
}
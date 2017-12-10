#include "DialogComponent.hpp"
#include "RenderComponent.h"

const unsigned int IBaseComponent<Component::DialogComponent>::typeID = 1004;
Core::String IBaseComponent<Component::DialogComponent>::componentName = "DialogComponent";

namespace Component
{
	DialogComponent::DialogComponent() :
		fontName("arial.ttf"),
		dialogMessage("NotSet"),
		position(0, 0),
		open(false), dCreated(false)//,msg(new GUI::FloatingText())
	{
		//rex = new sf::RenderTexture();
		//rex->create(128, 64);
		//msg->iconName = "test.png";
	}

	DialogComponent::DialogComponent(double dur) :
		fontName("arial.ttf"),
		dialogMessage("NotSet"),
		position(0, 0),
		open(false), dCreated(false)//, msg(new GUI::FloatingText())
	{
		//rex = new sf::RenderTexture();
		//rex->create(128, 64);
		//msg->iconName = "test.png";
		//msg->duration = dur;
	}
	DialogComponent::DialogComponent(const DialogComponent &diag) :
		fontName("arial.ttf"),
		dialogMessage(diag.dialogMessage),
		position(diag.position),
		open(false), dCreated(false)//, msg(new GUI::FloatingText(*diag.msg))
	{
		//rex = new sf::RenderTexture();
		//rex->create(128, 64);
	}

	DialogComponent::~DialogComponent()
	{
		//delete msg;
		//msg = nullptr;
		//Engine::GUI.removeDialog(*this);
		//delete rex;
	}

	DialogComponent * DialogComponent::copy() const
	{
		return new DialogComponent(*this);
	}
	void DialogComponent::attachOn(GameObject* go)
	{
		DialogComponent::BaseComponent::attachOn(go);
	}
	void DialogComponent::updateLocation()
	{
		//HIGH Fix this with floor and research more
		//msg->setPosition(attachedOn->GetComponent<TransformComponent>()->position.x - position.x + .51f,attachedOn->GetComponent<TransformComponent>()->position.y - position.y + .51f);
	}
	//TODO Remove either this one or the other createDialog
	void DialogComponent::createDialog(bool b)
	{
		//sprt.setTexture(*Engine::Graphic.requestTexture(msg->iconName));
		//rex->draw(sprt);
		//msg->setFont(Engine::Graphic.font.requestFont(fontName));
		//msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - position.x, this->attachedOn->GetComponent<TransformComponent>()->position.y - position.y);
		updateLocation();
		//msg->setFillColor(msg->color);
		//msg->setSize(12);
		//*msg = dialogMessage;
		//rex->draw(msg->text);
		//rex->display();
		//msg->iconSprite.setTexture(rex->getTexture());
		dCreated = true;
	}
	void DialogComponent::createDialog()
	{
		tryLoadTextureAndFont();

		//msg->setFillColor(msg->color);
		//msg->setSize(12);
		//*msg = dialogMessage;

		dCreated = true;
	}
	void DialogComponent::show()
	{
		updateLocation();
		if (!open)
		{
			//msg->timer.restart();

			//TODO: Fix this cause this apparently use alot of resources depedning on machine
			if (!dCreated)
				createDialog();
			//Engine::GUI.addDialog(*this);
			//Engine::Graphic.insertdrawableMessage(msg);
			open = true;
		}
	}
	void DialogComponent::close()
	{
		if (open)
		{
			//Engine::GUI.removeDialog(*this);
			//Engine::Graphic.removeFromMessageList(msg,false);
			open = false;
		}
	}
	bool DialogComponent::updateFromEditor()
	{
		tryLoadTextureAndFont();
		updateLocation();
		//msg->setPosition(this->attachedOn->GetComponent<TransformComponent>()->position.x - position.y,this->attachedOn->GetComponent<TransformComponent>()->position.y - position.y);
		//*msg = dialogMessage;

		return true;
	}

	void DialogComponent::tryLoadTextureAndFont()
	{
#ifdef _DEBUG
		//try
		//{
#endif
		//msg->setIcon(msg->iconName);
		//msg->setFont(Engine::Graphic.font.requestFont(fontName));

#ifdef _DEBUG
	//}
	//catch (GUI::MissingIconException ex)
	//{
		//MessageBox(Engine::Window.hWnd,"Missing Dialog Texture","Error:MissingDialogTexture",NULL);

		//msg->iconSprite.setTexture(*ex.what());
	//}
	//catch (GUI::MissingFontException ex)
	//{
		//MessageBox(Engine::Window.hWnd,"Missing Dialog Font","Error:MissingDialogFont",NULL);

		//msg->setFont(ex.what());
	//}
#endif
	}
}
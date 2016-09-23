#include "Button.hpp"

void GUI::Button::mouseDown()
{
	if (isPointInside(BaseHandler::mousePos) && enabled)
	{
		sendMessage(*this, Click);
		mouseState = (MouseState)(GUI::Down | GUI::Hold);
	}
}

void GUI::Button::mouseHandle()
{
	//Do nada
}

GUI::Button::Button() : BaseHandler(GUI::Type::e_Button)
{
}

GUI::Button::Button(const Button & copy) : BaseHandler(copy)
{
	Engine::Input.mouse.registerCallback(std::bind(&Button::mouseDown, this), sf::Mouse::Button::Left, Input::Press);
	//Engine::Input.mouse.registerCallback([this]() { mouseHandle(); }, sf::Mouse::Button::Left, Input::Hold);
	Engine::Input.mouse.registerCallback([this]()
	{
		if (isPointInside(BaseHandler::mousePos) && enabled && (mouseState & GUI::Hold))
		{
			sendMessage(*this, Click);
			mouseState = (MouseState)(mouseState | GUI::Up);
		}
		else mouseState = GUI::None;

		mouseUsed = false;
		Offset = Vector2(0, 0);
	}, sf::Mouse::Button::Left, Input::Release);
}

GUI::Button::Button(std::string buttonText, Vector2i size, Vector2 position, BaseHandler* parent) : BaseHandler(GUI::Type::e_Button)
{
	this->size = size;
	pos = position;
	this->parent = parent;
	if (parent->getType() == Type::e_Window)
		parentWindow = parent;
	sprite.setTexture(*Engine::Graphic.requestTexture("DefaultWindow_Old.png"));
	sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));


	Engine::Input.mouse.registerCallback( std::bind(&Button::mouseDown, this), sf::Mouse::Button::Left, Input::Press);
	Engine::Input.mouse.registerCallback([this]() { sendMessage(*this, Click); }, sf::Mouse::Button::Left, Input::Hold);
	Engine::Input.mouse.registerCallback([this]()
	{
		if (isPointInside(BaseHandler::mousePos) && enabled && (mouseState & GUI::Hold))
		{
			sendMessage(*this, Click);
			mouseState = (MouseState)(mouseState | GUI::Up);
		}
		else mouseState = GUI::None;

		mouseUsed = false;
		Offset = Vector2(0, 0);
	}, sf::Mouse::Button::Left, Input::Release);

}

unsigned int GUI::Button::handle(MessageType msg)
{
	switch (msg)
	{
	case GUI::Click:
	{
		if (mouseState & GUI::Down)
		{
			mouseState = (MouseState)(mouseState & ~GUI::Down);
			//send message to parent that if it want to move we deny it
			if (isPointInside(BaseHandler::mousePos) && parentWindow->hasFocus())
			{
				sendMessage(*this, GUI::ForceStopMove);
				preClick = true;
			}
			mouseUsed = true;
		}
		if (mouseState & GUI::Hold)
		{
			// remove the hold flag if the cursor moves outide the window area, ignore this check 
			//if we are moving the window as the cursor may pop outside the title frame.
			if (isPointInside(mousePos) && preClick)
			{
				// highlight the color when the button has been preClicked.
				sprite.setColor(sf::Color(125,125,255));
			}
			else if (isPointInside(mousePos))
			{
				//Highlight the button here 
				sprite.setColor(sf::Color(125,125,125));
			}
			else
			{
				// do not highlight the button.
				sprite.setColor(sf::Color(255,255,255));
			}
		}
		if (mouseState & GUI::Up)
		{
			mouseState = GUI::None;
			//remove highlight
			//if mouse inside commit the click function
			if (isPointInside(mousePos) && preClick )
				click();
			//force color reset
			sprite.setColor(sf::Color::White);
			preClick = false;
		}
		// else the click message is invalid, ignore it.
	}
		break;
	case GUI::Move:
		break;
	case GUI::ForceStopMove:
		if (parent)
			sendMessage(*parent, GUI::ForceStopMove);
		break;
	default:
		break;
	}
	return BaseHandler::handle(msg);
}

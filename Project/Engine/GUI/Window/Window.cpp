#include "Window.hpp"

bool GUI::Window::isPointInsideTitle(Vector2 & pos)
{
	return true;
}

//has to remove old gui stuff before cause namespace conflicts with name
void GUI::Window::mouseHandle()
{
	// returns true if the mouse is inside this window, and the window is open and enabled, it sends a click event;
	if(isPointInside(BaseHandler::mousePos) && enabled)
		sendMessage(*this, Click);
}

GUI::Window::Window() : BaseHandler(GUI::Type::e_Window)
{
	focus = true;
	// hardcoded values, create a real constructor instead that takes size and pos as arguments.
	size.x = 200;
	size.y = 200;

	pos.x = 200;
	pos.y = 200;

	sprite.setTexture(*Engine::Graphic.requestTexture("test.png"));
	sendMessage(*this, Move);
	sendMessage(*this, Resize);

	parent = NULL;
	Engine::Input.mouse.registerCallback([this]()
	{
		if (isPointInside(BaseHandler::mousePos) && enabled)
		{
			sendMessage(*this, Click);
			mouseState = (MouseState)(GUI::Down | GUI::Hold);
		}
		//else
			//; Do nothing
	}, sf::Mouse::Button::Left, Input::Press);
	Engine::Input.mouse.registerCallback([this]() { mouseHandle(); }, sf::Mouse::Button::Left, Input::Hold);
	Engine::Input.mouse.registerCallback([this]()
	{ 
		if (isPointInside(BaseHandler::mousePos) && enabled && (mouseState & GUI::Hold))
		{ 
			sendMessage(*this, Click);
			// add the GUI::UP state to the current mouseState;
			mouseState = (MouseState)(mouseState | GUI::Up);
		}
		else mouseState = GUI::None;

		// clear moving and offsetFlag on every mouse Up Event.
		moving = false;
		Offset = Vector2(0, 0);
	}, sf::Mouse::Button::Left, Input::Release);
}

unsigned int GUI::Window::handle(MessageType msg)
{
	switch (msg)
	{
	case GUI::Click:
	{
		if (mouseState & GUI::Down)
		{
			mouseState =(MouseState)(mouseState &~GUI::Down);
			if (isPointInsideTitle(BaseHandler::mousePos) && focus)
			{
				moving = true;
				// set an offset depending on where the mouse was clicked
				Offset = mousePos - pos;
				sendMessage(*this, GUI::SetMoveCoord);
			}
		}
		if (mouseState & GUI::Hold)
		{
			if(moving)
				sendMessage(*this, GUI::SetMoveCoord);
			// remove the hold flag if the cursor moves outide the window area, ignore this check 
			//if we are moving the window as the cursor may pop outside the title frame.
			if (!isPointInside(BaseHandler::mousePos) && !moving)
			{
				mouseState = (MouseState)(mouseState & ~GUI::Hold);
			}
		}
		if (mouseState & GUI::Up)
		{
			mouseState = GUI::None;
		}
		// else the click message is invalid, ignore it.
		// clear moving and resize variables

	}
		break;
	case GUI::Resize:
		if (resizeAble)
		{
			if (pos.x == 0)
			{
				int x1 = (int) BaseHandler::mousePos.x - pos.x;
				int y1 = (int) BaseHandler::mousePos.y - pos.y;
				if (x1 < minResizeSize.x)
					x1 = minResizeSize.x;
				if (y1 < minResizeSize.y)
					y1 = minResizeSize.y;
				size = Vector2i(x1, y1);
			}
			sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		}
		return 0;
	default:
		break;
	}
	return BaseHandler::handle(msg);
}

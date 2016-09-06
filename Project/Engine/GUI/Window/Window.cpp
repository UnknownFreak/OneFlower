#include "Window.hpp"

bool GUI::Window::isPointInsideTitle(Vector2 & pos)
{
	return false;
}

//has to remove old gui stuff before cause namespace conflicts with name
void GUI::Window::mouseHandle()
{
	// returns true if the mouse is inside this window, and the window is open and enabled, it sends a click event;
	if(isPointInside(ElementBase::mousePos) && enabled)
		sendMessage(*this, Click);
}

GUI::Window::Window() : ElementBase(GUI::Type::e_Window)
{

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
		if (isPointInside(ElementBase::mousePos) && enabled)
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
		if (isPointInside(ElementBase::mousePos) && enabled && (mouseState & GUI::Hold))
		{ 
			sendMessage(*this, Click);
			// add the GUI::UP state to the current mouseState;
			mouseState = (MouseState)(mouseState | GUI::Up);
		}
		else mouseState = GUI::None;
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
			std::cout << "mouseDown (window)\n";
			mouseState =(MouseState)(mouseState &~GUI::Down);
			if (isPointInsideTitle(ElementBase::mousePos) && focus)
			{
				moving = true;
				// set an offset depending on where the mouse was clicked
				sendMessage(*this, GUI::Move);
			}
		}
		if (mouseState & GUI::Hold)
		{
			std::cout << "mouseHold (window)\n";
			if(moving)
				sendMessage(*this, GUI::Move);
			// remove the hold flag if the cursor moves outide the window area
			if (!isPointInside(ElementBase::mousePos))
				mouseState = (MouseState) ( mouseState & ~GUI::Hold);
		}
		if (mouseState & GUI::Up)
		{
			std::cout << "mouseUp (window) \n";
			mouseState = GUI::None;
			moving = false;
		}
		// else the click message is invalid, ignore it.
	}
		break;
	case GUI::Resize:
		if (resizeAble)
		{
			if (pos.x == 0)
			{
				int x1 = (int) ElementBase::mousePos.x - pos.x;
				int y1 = (int) ElementBase::mousePos.y - pos.y;
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
	return ElementBase::handle(msg);
}

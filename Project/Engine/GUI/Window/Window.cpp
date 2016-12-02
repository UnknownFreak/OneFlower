#include "Window.hpp"

bool GUI::Window::isPointInsideTitle(Vector2 & point)
{
	return visible && point.x >= pos.x && point.x <= size.x + pos.x && point.y >= pos.y && point.y <= pos.y + titleHeight;
}

void GUI::Window::closeClick()
{
	sendMessage(*this, MessageType::Close);
}

void GUI::Window::resizeDrag()
{
	sendMessage(*this, GUI::SetResizeCoord);
}

void GUI::Window::resizPreClick()
{
	Offset = mousePos - resizeGrip.getPosition();
	sendMessage(*this, GUI::MessageType::SetResizeCoord);
}

//has to remove old gui stuff before cause namespace conflicts with name
void GUI::Window::mouseHold()
{
	BaseHandler::mouseHold();
	// returns true if the mouse is inside this window, and the window is open and enabled, it sends a click event;
	if (tookMouse && isPointInside(BaseHandler::mousePos) && enabled)
		sendMessage(*this, Click);
}
bool GUI::Window::mouseDown()
{
	BaseHandler::mouseDown();
	if (!mouseUsed && isPointInside(BaseHandler::mousePos) && enabled)
	{
		sendMessage(*this, Click);
		mouseState = (MouseState)(GUI::Down | GUI::Hold);
	}
	//else
	//; Do nothing
	return mouseUsed;
}


void GUI::Window::mouseUp()
{
	BaseHandler::mouseUp();
	if (isPointInside(BaseHandler::mousePos) && enabled && (mouseState & GUI::Hold))
	{
		sendMessage(*this, Click);
		mouseState = (MouseState)(mouseState | GUI::Up);
	}
	else mouseState = GUI::None;

	moving = false;
	mouseUsed = false;
	tookMouse = false;
	Offset = Vector2(0, 0);
}

GUI::Window::Window() : BaseHandler(GUI::Type::e_Window), close("X", { 30, 20 }, { 170, 0 }, this), resizeGrip("", { 20,20 }, {180,180},this)
{


	// hardcoded values, create a real constructor instead that takes size and pos as arguments.
	size.x = 200;
	size.y = 200;

	pos.x = 200;
	pos.y = 200;

	minResizeSize.x = 200;
	minResizeSize.y = 200;

	sprite.setTexture(*Engine::Graphic.requestTexture("test.png"));
	sendMessage(*this, Move);
	sendMessage(*this, Resize);
	sendMessage(*this, RequestFocus);

	parent = NULL;
	components.push_back(&close);
	components.push_back(&resizeGrip);
	// check why this button click crashes if the window is not focused. May be a requestfocus thing.
	close.click = std::bind(&Window::closeClick,this);
	resizeGrip.hold = std::bind(&Window::resizeDrag, this);
	resizeGrip.preClickfn = std::bind(&Window::resizPreClick, this);

	//Engine::Input.mouse.registerCallback([this]()
	//{
	//	mouseDown();
	//}, sf::Mouse::Button::Left, Input::Press);
	//Engine::Input.mouse.registerCallback([this]() { mouseHold(); }, sf::Mouse::Button::Left, Input::Hold);
	//Engine::Input.mouse.registerCallback([this]()
	//{ 
	//	
	//}, sf::Mouse::Button::Left, Input::Release);
}

unsigned int GUI::Window::handle(MessageType msg)
{
	switch (msg)
	{
	case GUI::Click:
	{
		if (mouseState & GUI::Down)
		{
			mouseState =(MouseState)(mouseState & ~GUI::Down);
			if (!focus && !mouseUsed)
			{
				sendMessage(*this, GUI::RequestFocus);
				// we requested focus in the title area, enable moving flag.
				if (isPointInsideTitle(mousePos))
				{
					moving = true;
					// set an offset depending on where the mouse was clicked
					Offset = mousePos - pos;
					sendMessage(*this, GUI::SetMoveCoord);
				}
			}
			else if (isPointInsideTitle(mousePos) && focus && !mouseUsed)
			{
				moving = true;
				// set an offset depending on where the mouse was clicked
				Offset = mousePos - pos;
				sendMessage(*this, GUI::SetMoveCoord);
			}
			mouseUsed = true;
			tookMouse = true;
			return 1;
		}
		if (mouseState & GUI::Hold)
		{
			if(moving)
				sendMessage(*this, GUI::SetMoveCoord);
			// remove the hold flag if the cursor moves outide the window area, ignore this check 
			//if we are moving the window as the cursor may pop outside the title frame.
			if (!isPointInside(mousePos) && !moving)
			{
				mouseState = (MouseState)(mouseState & ~GUI::Hold);
			}
		}
		if (mouseState & GUI::Up)
		{
			mouseState = GUI::None;
		}
		// else the click message is invalid, ignore it.

	}
		break;
	case GUI::Resize:
		if (resizeAble)
		{
			int x1 = (int) mousePos.x - Offset.x;
			int y1 = (int) mousePos.y - Offset.y;
			if (x1 < minResizeSize.x)
				x1 = minResizeSize.x;
			if (y1 < minResizeSize.y)
				y1 = minResizeSize.y;
			size = Vector2i(x1, y1);
			// set the new pos of the resize grip and the close button.
			close.setPosition({ size.x - (double) close.getSize().x, 0 });
			resizeGrip.setPosition({ size.x - (double)resizeGrip.getSize().x, size.y - (double)resizeGrip.getSize().y });
			sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		}
		return 0;
	case GUI::ForceStopMove:
	{
		moving = false;
		return 0;
	}
	default:
		break;
	}
	// call the default handle function
	return BaseHandler::handle(msg);
}

void GUI::Window::enableResizeMode()
{
	sendMessage(resizeGrip, GUI::Show);
}

void GUI::Window::disableResizeMode()
{
	sendMessage(resizeGrip, GUI::Hide);
}



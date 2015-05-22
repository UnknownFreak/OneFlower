#ifndef BaseWindow_HPP
#define BaseWindow_HPP

#include <SFML\Graphics\Sprite.hpp>
#include "Button.hpp"
#include "../Text/Message.hpp"
#include "../Vector.h"
class BaseWindow
{
public:

	BaseWindow(int x, int y, int sizeX, int sizeY, bool resizeable, std::string title);
	virtual ~BaseWindow() = default;
	
	bool open = false;
	bool focus = false;
	bool requestFocus = false;
	bool drawResizeIcon;

	sf::Sprite window;
	Vector2 position;
	
	void draw();
	void move();
	void WindowHandle();

	bool checkMouseInside();
protected:

	int inventoryButtonOffsets = 16;
	bool resizeing = false;
	bool moving = false;

	Button close;
	Button resize;
	
	Vector2 clickOffset;

	Message title;

	float offsetX = 0;
	float offsetY = 0;

	bool MouseInsideTitleBar();
	void checkMouseOffset(double&x, double &y);
	void Imove(double x, double y);
	void Iresize(double x, double y);
};


#endif
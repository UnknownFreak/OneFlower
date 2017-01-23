#ifndef RenderView_HPP
#define RenderView_HPP
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
//#include <Windows.h>
#include <Core/Vector.h>
class RenderView
{
public:
	RenderView();
	sf::View camera;
	sf::RenderWindow render;
	//HWND hWnd;
	//HWND viewport;
	bool docked = false;
private:
	Vector2i size;
};

#endif
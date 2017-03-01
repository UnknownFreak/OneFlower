#ifndef RenderView_HPP
#define RenderView_HPP
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <Core/Vector.h>
#include <Windows.h>
class RenderView
{
public:
	RenderView();
	sf::View camera;
	sf::RenderWindow render;
	//HWND hWnd;
	//HWND viewport;
	bool docked = false;
#ifdef _EDITOR_
	void init(HWND parent);
#else
	void init();
#endif
private:
	Core::Vector2i size;
};

#endif
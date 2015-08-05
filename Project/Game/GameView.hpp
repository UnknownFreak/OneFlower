#ifndef GameView_HPP
#define GameView_HPP
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <Windows.h>
#include "../Vector.h"
class GameView
{
public:
	GameView();
#ifdef _DEBUG
	~GameView();
#endif
	sf::View camera;
	sf::RenderWindow render;
	HWND hWnd;

	//HWND viewport;
	bool docked = false;
private:
	Vector2 size;
};

#endif
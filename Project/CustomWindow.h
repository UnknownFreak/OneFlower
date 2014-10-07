#ifndef CustomWindow_H
#define CustomWindow_H
#include <SFML\Graphics\RenderWindow.hpp>
#include <Windows.h>	
#include <map>
#include "Vector.h"
#include <string>
//Read Only
const sf::RenderWindow* RequestWindow();

//Returns a modifiyable pointer towards the main window
sf::RenderWindow* SetWindow();

//EditorWindow* SetEditorWindow();

class EditorWindow
{
public:
	sf::RenderWindow Window;
	void Update();
	






private:



};
#endif
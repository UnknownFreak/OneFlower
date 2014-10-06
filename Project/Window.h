#ifndef Window_H
#define Window_H
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
//Read Only
const sf::RenderWindow* RequestWindow();
sf::Event* RequestEvent();
//Returns a modifiyable pointer towards the main window
sf::RenderWindow* SetWindow();
sf::RenderWindow* SetEditWindow();
#endif
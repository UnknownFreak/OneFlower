#ifndef Keybind_HPP
#define Keybind_HPP
#include <SFML\Window\Keyboard.hpp>
#include <string>

struct Keybind
{
	sf::Keyboard::Key input;
	std::string action;
};

#endif
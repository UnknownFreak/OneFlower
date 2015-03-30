#ifndef Input_HPP
#define Input_HPP
#include <SFML\Graphics\Sprite.hpp>
#include <vector>
#include <string>
#include "Keybind.hpp"

class InputHandler
{
public:
	InputHandler();
	//Checks for input on each keybind and returns a vector of strings with the actions to be executed
	std::vector<std::string> getInput();
private:
	std::vector<Keybind> keybinds;
};

#endif
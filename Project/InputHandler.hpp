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
	std::vector<std::string> getInput();
private:
	std::vector<Keybind> keybinds;




};

#endif
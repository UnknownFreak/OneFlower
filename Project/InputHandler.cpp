#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include "InputHandler.hpp"

//Initiates all keybinds and puts them in the "keybinds" vector
InputHandler::InputHandler()
{
	Keybind Jump = {sf::Keyboard::Key::W,"Jump"};
	Keybind Duck = {sf::Keyboard::Key::S,"Duck"};
	Keybind MoveLeft = {sf::Keyboard::Key::Left,"MoveLeft"};
	Keybind MoveRight = {sf::Keyboard::Key::Right,"MoveRight"};
	Keybind SpellSlot1 = {sf::Keyboard::Key::Num1,"SpellSlot1"};
	Keybind SpellSlot2 = {sf::Keyboard::Key::Num2,"SpellSlot2"};
	Keybind SpellSlot3 = {sf::Keyboard::Key::Num3,"SpellSlot3"};
	Keybind SpellSlot4 = {sf::Keyboard::Key::Num4,"SpellSlot4"};
	Keybind Menu = {sf::Keyboard::Key::Escape,"Menu"};
	Keybind Inventory = {sf::Keyboard::Key::I,"Inventory"};

	keybinds.push_back(Jump);
	keybinds.push_back(Duck);
	keybinds.push_back(MoveLeft);
	keybinds.push_back(MoveRight);
	keybinds.push_back(SpellSlot1);
	keybinds.push_back(SpellSlot2);
	keybinds.push_back(SpellSlot3);
	keybinds.push_back(SpellSlot4);
	keybinds.push_back(Menu);
	keybinds.push_back(Inventory);
}

//Checks for input on each keybind and returns a vector of strings with the actions to be executed
std::vector<std::string> InputHandler::getInput()
{
	std::vector<std::string> inputs;

	for(std::vector<Keybind>::iterator it = keybinds.begin(); it != keybinds.end(); ++it)
	{
		if(sf::Keyboard::isKeyPressed((it)->input))
			inputs.push_back((it)->action);
	}
	return inputs;
}
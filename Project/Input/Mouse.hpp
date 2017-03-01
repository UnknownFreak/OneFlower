#ifndef Mouse_HPP
#define Mouse_HPP

#include <SFML\Window\Mouse.hpp>
#include <Core/Vector.h>
#include <vector>
#include <map>
#include <functional>
#include "InputEnum.hpp"

class GameObject;
class Mouse
{
public:

	Mouse();
	std::vector<GameObject*> list;
	GameObject* mySelected;
	//World pos;
	Core::Vector2 pos;
	Core::Vector2 offset;
	void update();
	int deltaScrolls = 0;
	float scrollSpeed = 0.05f;

	void registerCallback(std::function<void(void)> callback, sf::Mouse::Button button, Input::Action actionType);

private:

	bool resetDxDy = true;
	bool moving = false;
	Core::Vector2 dxDy;

	std::map<sf::Mouse::Button, std::vector<std::function<void(void)>>> bindsOnPress;
	std::map<sf::Mouse::Button, std::vector<std::function<void(void)>>> bindsOnRelease;
	std::map<sf::Mouse::Button, std::vector<std::function<void(void)>>> bindsOnHold;
	std::vector<sf::Mouse::Button> callbackRelease;
};

#endif //Mouse_HPP
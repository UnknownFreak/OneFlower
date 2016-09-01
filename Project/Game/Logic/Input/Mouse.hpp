#ifndef Mouse_HPP
#define Mouse_HPP

#include <SFML\Window\Mouse.hpp>
#include "../../../Vector.h"
#include <vector>

//tmp
#include "../../Skills/Skill.hpp"

class GameObject;
class Mouse
{
public:
	bool RMBPressed;
	bool LMBPressed;
	Mouse();
	std::vector<GameObject*> list;
	GameObject* mySelected;
	//World pos;
	Vector2 pos;
	Vector2 offset;
	void update();
	bool leftClick();
	bool rightClick();
	int deltaScrolls = 0;
	float scrollSpeed = 0.05f;

private:
	bool resetDxDy = true;
	bool moving = false;
	Vector2 dxDy;

	std::map<sf::Mouse::Button, std::vector<std::function<void(void)>>> bindsOnPress;
	std::map<sf::Mouse::Button, std::vector<std::function<void(void)>>> bindsOnRelease;
	std::map<sf::Mouse::Button, std::vector<std::function<void(void)>>> bindsOnHold;
	std::vector<sf::Mouse::Button> callbackRelease;

};

#endif //Mouse_HPP
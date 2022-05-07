#ifndef Controller_HPP
#define Controller_HPP

#include <map>
#include <Helpers/Enum/InputEnum.hpp>

class Controller
{
	unsigned buttonCount;
	unsigned controllerNumber;
public:
	static std::map<unsigned, Controller> controllers;
	static bool isButtonPressed(Enums::Input::ControllerButtons button);
	//static float getControllerAxisPos(sf::Joystick::Axis axis);
	static void update();
	static bool getControllers;
	static Controller& currentController;


	Controller(const unsigned& controllerNumber, const unsigned& buttonCount);
	Controller& operator=(const Controller& r);

	bool isAnyButtonPressed() const;
	bool isAnyAxisChanged() const;
};


#endif
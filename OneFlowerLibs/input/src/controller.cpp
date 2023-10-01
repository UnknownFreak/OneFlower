#include <vector>

#include <input/controller.hpp>

std::map<unsigned, Controller> Controller::controllers;
bool Controller::getControllers = true;
Controller undefined = Controller(0xff, 0xff);
Controller& Controller::currentController = undefined;

bool Controller::isButtonPressed(of::input::ControllerButtons button)
{
	button;
	//if (currentController.controllerNumber != 0xff)
	//	return sf::Joystick::isButtonPressed(currentController.controllerNumber, (unsigned)button);
	return false;
}

//float Controller::getControllerAxisPos(sf::Joystick::Axis axis)
//{
//	if (currentController.controllerNumber != 0xff)
//		return sf::Joystick::getAxisPosition(currentController.controllerNumber, axis);
//	return 0.f;
//}

void Controller::update()
{
	//if (getControllers)
	//{
	//	getControllers = false;
	//	for (unsigned i = 0; i < 8; i++)
	//	{
	//		if (sf::Joystick::isConnected(i))
	//		{
	//			const unsigned buttonCount = sf::Joystick::getButtonCount(i);
	//			controllers.try_emplace(i, Controller(i, buttonCount));
	//		}
	//	}
	//}
	//if (currentController.controllerNumber == 0xff)
	//	for (std::map<unsigned, Controller>::const_iterator it = controllers.begin();
	//		it != controllers.end();
	//		it++)
	//	{
	//		if (it->second.isAnyButtonPressed() || it->second.isAnyAxisChanged())
	//			currentController = it->second;
	//	}
}

Controller::Controller(const unsigned& controllerNumber, const unsigned& buttonCount) : 
	controllerNumber(controllerNumber),
	buttonCount(buttonCount)
{
}

Controller & Controller::operator=(const Controller & r)
{
	controllerNumber = r.controllerNumber;
	buttonCount = r.buttonCount;
	return *this;
}

bool Controller::isAnyButtonPressed() const
{
	//for (unsigned i = 0; i < buttonCount; i++)
	//{
	//	if (sf::Joystick::isButtonPressed(controllerNumber, i))
	//		return true;
	//}
	return false;
}

bool Controller::isAnyAxisChanged() const
{
	return false;
	//return 
	//	sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::Axis::X) > 0.5 ||
	//	sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::Axis::X) < -0.5 ||
	//	sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::Axis::Y) > 0.5 ||
	//	sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::Axis::Y) < -0.5 ||
	//	sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::Axis::Z) > 0.5 ||
	//	sf::Joystick::getAxisPosition(controllerNumber, sf::Joystick::Axis::Z) < -0.5;
}

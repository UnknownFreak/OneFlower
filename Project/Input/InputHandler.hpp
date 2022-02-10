#ifndef InputHandler_HPP_A
#define InputHandler_HPP_A

#include <functional>
#include <map>
#include <vector>

#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML/Window/Joystick.hpp>

#include <Interfaces\IEngineModule.hpp>

#include "BasicInputHandler.hpp"
#include "AxisInputHandler.hpp"

namespace Input
{
	class InputHandler : public Interfaces::IEngineResource<InputHandler>
	{
		bool isPlayerKeyboardInputEnabled = true;
	public:
		static bool isMovementEnabled;
		static bool skipCurrentFrame;

		void update(const float& fElapsedTime);

		BasicInputHandler<Enums::Input::ControllerButtons> controller;
		AxisCallbackholder<sf::Joystick::Axis> controllerAxis;
		BasicInputHandler<sf::Keyboard::Key> playerKeyboard;
		BasicInputHandler<sf::Keyboard::Key> uiKeyboard;
		BasicInputHandler<sf::Mouse::Button> mouse;

		Enums::EngineResourceType& getType() const
		{
			return type;
		}

		InputHandler();
		void togglePlayerInput();
		void disablePlayerMovement();
		void enablePlayerMovement();

		bool isConsoleEnabled() const;

		int deltaScrolls = 0;

	private:

	};
}

#endif
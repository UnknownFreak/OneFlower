#include "InputHandler.hpp"
#include "Controller.hpp"

of::module::EngineResourceType of::module::interface::IEngineResource<Input::InputHandler>::type = of::module::EngineResourceType::Input;
bool Input::InputHandler::isMovementEnabled = true;
bool Input::InputHandler::skipCurrentFrame = true;

namespace Input
{
	void InputHandler::update(const float& fElapsedTime)
	{
		// Update all controllers
		Controller::update();
		// poll the event handlers -- not to be confused with updating the state of the controller.
		controller.update(fElapsedTime);
		//controllerAxis.update(fElapsedTime);
		mouse.update(fElapsedTime);
		uiKeyboard.update(fElapsedTime);
		if (isPlayerKeyboardInputEnabled)
			playerKeyboard.update(fElapsedTime);
		skipCurrentFrame = false;
	}

	InputHandler::InputHandler() : playerKeyboard(swizzle::input::IsKeyPressed), uiKeyboard(swizzle::input::IsKeyPressed), mouse(swizzle::input::IsMouseButtonPressed), controller(Controller::isButtonPressed)
	//,controllerAxis(Controller::getControllerAxisPos)
	{
	}
	void InputHandler::togglePlayerInput()
	{
		isPlayerKeyboardInputEnabled = !isPlayerKeyboardInputEnabled;
	}
	void InputHandler::disablePlayerMovement()
	{
		isMovementEnabled = false;
	}
	void InputHandler::enablePlayerMovement()
	{
		isMovementEnabled = true;
	}
	bool InputHandler::isConsoleEnabled() const
	{
		return !isPlayerKeyboardInputEnabled;
	}
}

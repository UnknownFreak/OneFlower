#include <input/inputHandler.hpp>
#include <input/controller.hpp>

of::module::EngineResourceType of::module::interface::IEngineResource<of::input::InputHandler>::type = of::module::EngineResourceType::Input;
bool of::input::InputHandler::isMovementEnabled = true;
bool of::input::InputHandler::skipCurrentFrame = true;

namespace of::input
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
	, parser("keybinds.ini")
	{
	}

	InputHandler::~InputHandler()
	{
		parser.save();
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

	bool InputHandler::wasKeyPressed(const swizzle::input::Keys& key) const
	{
		return swizzle::input::WasKeyPressedThisFrame(key);
	}
}

#pragma once
#ifndef InputHandler_HPP_A
#define InputHandler_HPP_A

#include <functional>
#include <map>
#include <vector>

#include <swizzle/core/Input.hpp>

#include <module/IEngineModule.hpp>
#include <module/ModuleManager.hpp>

#include <input/inputType.hpp>
#include "BasicInputHandler.hpp"
#include "AxisInputHandler.hpp"

namespace of::input
{
	class InputHandler : public of::module::interface::IEngineResource<InputHandler>
	{
		bool isPlayerKeyboardInputEnabled = true;
	public:
		static bool isMovementEnabled;
		static bool skipCurrentFrame;

		void update(const float& fElapsedTime);

		BasicInputHandler<of::input::ControllerButtons> controller;
		//AxisCallbackholder<sf::Joystick::Axis> controllerAxis;
		BasicInputHandler<swizzle::input::Keys> playerKeyboard;
		BasicInputHandler<swizzle::input::Keys> uiKeyboard;
		BasicInputHandler<swizzle::input::Mouse> mouse;

		of::module::EngineResourceType& getType() const
		{
			return type;
		}

		InputHandler();
		void togglePlayerInput();
		void disablePlayerMovement();
		void enablePlayerMovement();

		bool isConsoleEnabled() const;
		bool wasKeyPressed(const swizzle::input::Keys& keyType) const;

		int deltaScrolls = 0;

	private:

	};
}

//namespace std
//{
//	template<>
//	struct hash<swizzle::input::KeyAction>
//	{
//		using argument_type = swizzle::input::KeyAction;
//
//		inline size_t operator()(argument_type const& input) const
//		{
//			std::string s = std::to_string((int)input.mKey) + std::to_string((int)input.mOptionalKey);
//			return std::hash<std::string>()(s);
//		}
//	};
//}

#endif
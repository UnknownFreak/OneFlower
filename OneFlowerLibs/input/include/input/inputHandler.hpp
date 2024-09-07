#pragma once

#include <functional>
#include <map>
#include <vector>

#include <swizzle/core/Input.hpp>

#include <input/inputType.hpp>
#include "BasicInputHandler.hpp"
#include "AxisInputHandler.hpp"

#include <utils/config/parser.hpp>

namespace of::input
{
	class InputHandler
	{
		bool isPlayerKeyboardInputEnabled = true;

		of::config::ConfigParser parser;

	public:
		static bool isMovementEnabled;
		static bool skipCurrentFrame;

		void update(const float fElapsedTime);

		BasicInputHandler<of::input::ControllerButtons> controller;
		//AxisCallbackholder<sf::Joystick::Axis> controllerAxis;
		BasicInputHandler<swizzle::input::Keys> playerKeyboard;
		BasicInputHandler<swizzle::input::Keys> uiKeyboard;
		BasicInputHandler<swizzle::input::Mouse> mouse;

		InputHandler();
		~InputHandler();

		void togglePlayerInput();
		void disablePlayerMovement();
		void enablePlayerMovement();

		bool isConsoleEnabled() const;

		bool wasKeybindPressed(const of::common::String& keybind);

	private:
		bool wasKeyPressed(const swizzle::input::Keys& keyType) const;
		bool wasControllerButtonPressed(const of::input::ControllerButtons& button) const;
	public:
		// TODO: fix and write readable keybind value to ini file.
		swizzle::input::Keys getKeybind(const of::common::String& keybindName)
		{
			int key = parser.get("keyboard", keybindName, (int)swizzle::input::Keys::KeyNone);
			return (swizzle::input::Keys)key;
		}

		void setKeybind(const of::common::String& keybind, const swizzle::input::Keys key)
		{
			parser.put("keyboard", keybind, (int)key);
		}

		of::input::ControllerButtons getControllerKeybind(const of::common::String& keybindName)
		{
			int key = parser.get("controller", keybindName, (int)of::input::ControllerButtons::HOME);
			return (of::input::ControllerButtons)key;
		}

		void setControllerKeybind(const of::common::String& keybind, const of::input::ControllerButtons button)
		{
			parser.put("controller", keybind, (int)button);
		}

		static void SetInputSource(std::weak_ptr<InputHandler> source);
		static std::weak_ptr<InputHandler> GetInputSource();

		int deltaScrolls = 0;

	private:

		static inline std::weak_ptr<InputHandler> sInputSource;

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

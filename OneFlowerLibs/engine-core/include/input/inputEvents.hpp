#pragma once

#include <input/inputFwdDeclare.hpp>

namespace of::input
{
	struct ButtonState
	{
		bool press;
		bool hold;
		bool release;
	};

	struct AxisState
	{
		float current;
		float previous = -100.f;
	};

	enum class InputType
	{
		Mouse,
		Keyboard,
		GamePadButton,
	};

	enum class InputStateType
	{
		Press,
		Hold,
		Release,
	};

	struct AxisEvent
	{
		GamePadAxis axis;
		float valueType;
	};

	struct InputEvent
	{
		InputType inputType;
		U32 valueType;
		inline Mouse getMouseButton() const { return (Mouse)valueType; }
		inline Keys getKeyboardKey() const { return (Keys)valueType; }
		inline GamePadButton getControllerButton() const { return (GamePadButton)valueType; }
	};
}
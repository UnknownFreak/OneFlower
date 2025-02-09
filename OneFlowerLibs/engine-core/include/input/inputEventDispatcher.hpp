#pragma once

#include <utils/lifetime/isAlive.hpp>
#include <input/inputFwdDeclare.hpp>

namespace of::input
{

	struct InputEventDispatcher : public of::utils::lifetime::IsAlive
	{
		std::unordered_map<Keys, ButtonState> mKeysValues;
		std::unordered_map<Mouse, ButtonState> mMouseButtonValues;

		std::unordered_map<GamePadAxis, AxisState> mGamePadAxisValues;
		std::unordered_map<GamePadButton, ButtonState> mGamePadButtonValues;
	};
}
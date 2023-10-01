#pragma once

namespace of
{
	namespace input
	{
		enum class Action
		{
			Press = 1 << 0,
			Hold = 1 << 1,
			Release = 1 << 2
		};

		enum class ControllerButtons
		{
			XB_A = 0,
			PS_X = 0,
			XB_B = 1,
			PS_CIRCLE = 1,
			XB_X = 2,
			PS_SQUARE = 2,
			XB_Y = 3,
			PS_TRIANGLE = 3,
			START,
			MENU,
			HOME,

		};
	};
}

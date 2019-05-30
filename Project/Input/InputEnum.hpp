#ifndef INPUTENUM_HPP
#define INPUTENUM_HPP

namespace Input
{
	enum Action
	{
		Press = 1 << 0,
		Hold = 1 << 1,
		Release = 1 << 2
	};
};

#endif
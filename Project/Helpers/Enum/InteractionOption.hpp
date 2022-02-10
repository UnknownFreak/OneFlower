#ifndef InteractionOption_HPP
#define InteractionOption_HPP
#include <string>

namespace Enums
{
	enum class InteractionOption
	{
		Up,
		Down,
		Left,
		Right,
		Select,
		Close,
	};

	inline std::string to_string(const InteractionOption& idx)
	{
		switch (idx)
		{
		case InteractionOption::Down:
			return "Down";
		case InteractionOption::Up:
			return "Up";
		case InteractionOption::Left:
			return "Left";
		case InteractionOption::Right:
			return "Right";
		case InteractionOption::Select:
			return "Select";
		case InteractionOption::Close:
			return "Close";
		default:
			return "Unknown";
		}
	}
}

#endif
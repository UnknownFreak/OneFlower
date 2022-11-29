#ifndef Rarity_HPP
#define Rarity_HPP

#include <utils/common/String.hpp>

namespace Enums
{
	enum class Rarity
	{
		Common,
		Fine,
		Rare,
		Epic,
		Legendary,
		Unknown = 255
	};

	inline of::common::String to_string(const Rarity& ths)
	{
		switch (ths)
		{
		case Rarity::Common:
			return "Common";
		case Rarity::Fine:
			return "Fine";
		case Rarity::Rare:
			return "Rare";
		case Rarity::Epic:
			return "Epic";
		case Rarity::Legendary:
			return "Legendary";
		default:
			break;
		}
		return "Unknown";
	}
}


#endif
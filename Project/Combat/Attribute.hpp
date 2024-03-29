#ifndef CAttribute_HPP
#define CAttribute_HPP

#include <Helpers/Enum/Attribute.hpp>
#include <Helpers/String.hpp>

namespace Combat
{
	struct Attribute
	{
		double baseValue;
		double valuePerLevel;
		double valueFromItems;
		double modifierPercent;
		size_t* level= 0;

		inline double getStatValue() const
		{
			return baseValue + (valuePerLevel * *level) + (valueFromItems * modifierPercent);
		}

		inline double getStatDividedBy(const double& divisor) const
		{
			return getStatValue() / divisor;
		}

	};
}

#endif
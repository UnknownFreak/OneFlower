#ifndef CAttribute_HPP
#define CAttribute_HPP

#include <utils/common/String.hpp>

namespace of::combat
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
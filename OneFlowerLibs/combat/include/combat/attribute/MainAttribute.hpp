#ifndef MainAttribute_HPP
#define MainAttribute_HPP

#include "Attribute.hpp"
#include <utils/common/String.hpp>
#include <vector>
#include <utility>

namespace of::combat
{
	struct MainAttribute
	{
		std::vector<std::pair<Attribute&, double>> attribute;

		double max;
		double current;
		double modifier;

		inline double getValue()
		{
			double val = 0;
			for (auto& x : attribute)
				val += x.first.getStatValue() * x.second;
			return val + modifier;
		}

	};
	struct StatAttribute
	{
		std::vector<std::pair<Attribute&, double>> attribute;

		double value;
		double modifier;

		inline double getValue()
		{
			double val = 0;
			for (auto& x : attribute)
				val += x.first.getStatValue() * x.second;
			return val + modifier;
		}
	};


	struct PercentualAttribute
	{
		std::vector<std::pair<Attribute&, double>> attribute;
		double div;
		double mod;

		double value;
		double modifier;

		inline double getValue()
		{
			double val = 0;
			for (auto& x : attribute)
				val += x.first.getStatDividedBy(div) * x.second;
			return val + mod + modifier;
		}
	};
}
#endif
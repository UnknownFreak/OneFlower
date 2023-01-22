#ifndef Barrier_HPP
#define Barrier_HPP

#include <vector>

namespace of::combat
{
	struct Barrier
	{
		typedef double remainingDamage;
		std::vector < std::pair<float, double>> barriers;

		void add(const float& time, const double& strength);
		void tick(const float& dt);
		remainingDamage doDamage(double damage, const double& multiplier);

		double totalBarrier;
	};
}

#endif
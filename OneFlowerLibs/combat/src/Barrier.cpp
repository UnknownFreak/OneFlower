#include <combat/Barrier.hpp>

namespace of::combat
{
	void Barrier::add(const float& time, const double& strength)
	{
		totalBarrier += strength;
		barriers.push_back({ time, strength });
	}

	void Barrier::tick(const float& dt)
	{
		auto it = barriers.begin();
		while (it != barriers.end())
		{
			it->first -= dt;
			if (it->first < 0)
			{
				totalBarrier -= it->second;
				it = barriers.erase(it);
			}
			else
				it++;
		}
	}

	Barrier::remainingDamage Barrier::doDamage(double damage, const double& multiplier)
	{
		auto it = barriers.begin();
		while (it != barriers.end() && damage > 0)
		{
			auto remainingDamage = it->second - damage;
			auto actualDamageDealt = it->second - (damage * multiplier);
			if (actualDamageDealt < 0)
			{
				totalBarrier -= it->second;
				it->second = 0;
				it = barriers.erase(it);
				damage = abs(remainingDamage);
			}
			else
			{
				it->second -= damage * multiplier;
				totalBarrier -= damage * multiplier;
				damage = 0;
				it++;
			}
		}
		return damage;
	}
};

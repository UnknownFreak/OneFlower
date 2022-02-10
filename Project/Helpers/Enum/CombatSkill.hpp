#ifndef CombatSkill_HPP
#define CombatSkill_HPP

#include <Helpers/String.hpp>

namespace Enums
{
	enum class CombatSkill
	{
		Primary,
		Secondary,
		Special,
		Chain,
	};

	inline Core::String to_string(const CombatSkill& skill)
	{
		switch (skill)
		{
		case CombatSkill::Primary: return "Primary";
		case CombatSkill::Secondary: return "Secondary";
		case CombatSkill::Special: return "Special";
		case CombatSkill::Chain: return "Chain";
		default:
			break;
		}
		return "Unknown";
	}

}


#endif
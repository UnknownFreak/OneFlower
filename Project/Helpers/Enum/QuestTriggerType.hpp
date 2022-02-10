#ifndef QuestTriggerType_HPP
#define QuestTriggerType_HPP

#include <Helpers/String.hpp>

namespace Enums
{
	enum class QuestTriggerType
	{
		Start,
		Fail,
		Reset,
		Progress,
	};

	// Is this needed??? it's never gonna be printed :think:
	inline Core::String to_string(const QuestTriggerType& typ)
	{
		switch (typ)
		{
		case QuestTriggerType::Start: return "Start";
		case QuestTriggerType::Fail: return "Fail";
		case QuestTriggerType::Reset: return "Reset";
		case QuestTriggerType::Progress: return "Progress";
		default:
			break;
		}
		return "Unknown";
	}

}


#endif
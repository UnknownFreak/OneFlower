#ifndef QuestState_HPP
#define QuestState_HPP

namespace Enums
{
	enum class QuestState
	{
		NOT_ACTIVE,
		ACTIVE,
		PENDING_COMPLETE,
		PENDING_FAILURE,
		COMPLETE,
		FAILED,
	};
}

#endif
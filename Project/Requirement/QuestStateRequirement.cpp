#include "QuestStateRequirement.hpp"

#include <session/gameSession.hpp>

namespace Requirement
{

	bool QuestStateRequirment::fullfilled()
	{
		auto& saveFile = of::session::get();
		saveFile;
		// TODO: Replace with QuestSaveState
		//if (saveFile.isQuestStored(questId))
		//{
		//	auto& state = saveFile.getQuestState(questId);
		//	if (checkObjective)
		//	{
		//		if (state.objectiveStates.find(objectiveId) == state.objectiveStates.end())
		//		{
		//			auto& logger = of::logger::get().getLogger("Questing::QuestStateRequirement");
		//			logger.Warning("QuestStateRequirement for objective state cannot be checked for as it does not exist in the quest state.", logger.fileInfo(__FILE__, __LINE__));
		//			return false;
		//		}
		//		return state.objectiveStates[objectiveId].state == questState;
		//	}
		//	return state.questState == questState;
		//}
		return false;
	}

	std::unique_ptr<Requirement> QuestStateRequirment::clone() const
	{
		return std::make_unique<QuestStateRequirment>(*this);
	}
}

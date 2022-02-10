#include "QuestStateRequirement.hpp"

#include <File/SaveFile.hpp>

namespace Requirement
{

	bool QuestStateRequirment::fullfilled()
	{
		auto& saveFile = Engine::GetModule<File::SaveFile>();
		if (saveFile.isQuestStored(questId))
		{
			auto& state = saveFile.getQuestState(questId);
			if (checkObjective)
			{
				if (state.objectiveStates.find(objectiveId) == state.objectiveStates.end())
				{
					Engine::GetModule<EngineModule::Logger::OneLogger>().Warning("QuestStateRequirement for objective state cannot be checked for as it does not exist in the quest state.", __FILE__, __LINE__);
					return false;
				}
				return state.objectiveStates[objectiveId].state == questState;
			}
			return state.questState == questState;
		}
		return false;
	}

	std::unique_ptr<Requirement> QuestStateRequirment::clone() const
	{
		return std::make_unique<QuestStateRequirment>(*this);
	}
}

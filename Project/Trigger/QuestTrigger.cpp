#include "QuestTrigger.hpp"

namespace Trigger
{
	void QuestTrigger::executeInternal()
	{
		// auto& questing = Engine::GetModule<Questing::Questing>();
		auto questing = tmp();
		switch (triggerType)
		{
		case Enums::QuestTriggerType::Start:
			questing.start(questId);
			break;
		case Enums::QuestTriggerType::Fail:
			questing.fail(questId);
			break;
		case Enums::QuestTriggerType::Reset:
			questing.reset(questId);
			break;
		case Enums::QuestTriggerType::Progress:
			questing.progress(questId);
			break;
		default:
			break;
		}
	}
	std::unique_ptr<of::trigger::Trigger> QuestTrigger::clone() const
	{
		return std::make_unique<QuestTrigger>(*this);
	}
}
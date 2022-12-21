#include "TriggerList.hpp"


namespace Trigger
{
	void TriggerList::executeInternal()
	{
		for (auto& trigger : triggerList)
		{
			trigger->execute();
		}
	}
	std::unique_ptr<of::resource::trigger::Trigger> TriggerList::clone() const
	{
		std::vector<std::unique_ptr<Trigger>> tmp;
		for (auto& t : triggerList)
			tmp.push_back(t->clone());

		auto p = std::unique_ptr<TriggerList>(new TriggerList());
		p->triggerOnce = triggerOnce;
		p->uuid = uuid;
		p->triggerList = std::move(tmp);
		return p;
	}
}
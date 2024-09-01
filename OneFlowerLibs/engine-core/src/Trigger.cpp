#include <trigger/Trigger.hpp>

#include <trigger/TriggerState.hpp>

#include <file/SaveFile.hpp>

namespace of::trigger
{
	void Trigger::execute()
	{
		auto& saveFile = of::session::get();

		auto exists = saveFile.exists(of::file::FileId(uuid), of::session::SaveStateTypeRef<of::trigger::TriggerState>::type);
		if (exists)
		{
			exists = saveFile.getState<TriggerState>(of::file::FileId(uuid))->triggered;
		}

		if (triggerOnce && exists)
			return;

		executeInternal();
		if (triggerOnce)
		{
			saveFile.setState(of::file::FileId(uuid), std::make_unique<TriggerState>(true));
		}
	}
}
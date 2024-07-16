#include <trigger/Trigger.hpp>

#include <trigger/TriggerState.hpp>

#include <module/SaveFile.hpp>

namespace of::trigger
{
	void Trigger::execute()
	{
		auto& saveFile = of::engine::GetModule<of::module::SaveFile>();

		auto exists = saveFile.exists(of::file::FileId(uuid), of::module::save_state::SaveStateTypeRef<of::trigger::TriggerState>::type);
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
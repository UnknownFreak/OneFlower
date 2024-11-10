#include <trigger/Trigger.hpp>

#include <trigger/TriggerState.hpp>

#include <session/gameSession.hpp>

namespace of::trigger
{
	void Trigger::execute()
	{
		auto& saveFile = of::session::get();

		auto exists = saveFile.exists(of::asset::AssetId(uuid), of::session::SaveStateTypeRef<of::trigger::TriggerState>::type);
		if (exists)
		{
			exists = saveFile.getState<TriggerState>(of::asset::AssetId(uuid))->triggered;
		}

		if (triggerOnce && exists)
			return;

		executeInternal();
		if (triggerOnce)
		{
			saveFile.setState(of::asset::AssetId(uuid), std::make_unique<TriggerState>(true));
		}
	}
}
#include <resource/trigger/TriggerState.hpp>

of::common::String of::module::save_state::SaveStateTypeRef<of::resource::trigger::TriggerState>::type = "TriggerState";

namespace of::resource::trigger
{
	common::String TriggerState::getType() const
	{
		return of::module::save_state::SaveStateTypeRef<SaveState>::type;
	}

	TriggerState::TriggerState() : TriggerState(false)
	{
	}

	TriggerState::TriggerState(bool triggered) : SaveState(of::module::save_state::SaveStateTypeRef<SaveState>::type), triggered(triggered)
	{
	}
}
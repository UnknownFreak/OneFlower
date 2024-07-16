#include <trigger/TriggerState.hpp>

of::common::String of::module::save_state::SaveStateTypeRef<of::trigger::TriggerState>::type = "TriggerState";

namespace of::trigger
{
	common::String TriggerState::getType() const
	{
		return of::module::save_state::SaveStateTypeRef<TriggerState>::type;
	}

	TriggerState::TriggerState() : TriggerState(false)
	{
	}

	TriggerState::TriggerState(bool triggered) : SaveState(of::module::save_state::SaveStateTypeRef<TriggerState>::type), triggered(triggered)
	{
	}
}
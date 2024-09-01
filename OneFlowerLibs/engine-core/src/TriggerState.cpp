#include <trigger/TriggerState.hpp>

of::common::String of::session::SaveStateTypeRef<of::trigger::TriggerState>::type = "TriggerState";

namespace of::trigger
{
	common::String TriggerState::getType() const
	{
		return of::session::SaveStateTypeRef<TriggerState>::type;
	}

	TriggerState::TriggerState() : TriggerState(false)
	{
	}

	TriggerState::TriggerState(bool triggered) : SaveState(of::session::SaveStateTypeRef<TriggerState>::type), triggered(triggered)
	{
	}
}
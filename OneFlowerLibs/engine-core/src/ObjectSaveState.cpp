#include <object/ObjectSaveState.hpp>

of::common::String of::module::save_state::SaveStateTypeRef<of::object::ObjectSaveState>::type = "ObjectSaveState";

namespace of::object
{
	common::String ObjectSaveState::getType() const
	{
		return of::module::save_state::SaveStateTypeRef<ObjectSaveState>::type;
	}
	
	ObjectSaveState::ObjectSaveState(): SaveState(of::module::save_state::SaveStateTypeRef<ObjectSaveState>::type), objectSaveStates()
	{
	}
}
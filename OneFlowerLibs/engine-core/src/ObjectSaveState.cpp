#include <object/ObjectSaveState.hpp>

of::common::String of::session::SaveStateTypeRef<of::object::ObjectSaveState>::type = "ObjectSaveState";

namespace of::object
{
	common::String ObjectSaveState::getType() const
	{
		return of::session::SaveStateTypeRef<ObjectSaveState>::type;
	}
	
	ObjectSaveState::ObjectSaveState(): SaveState(of::session::SaveStateTypeRef<ObjectSaveState>::type), objectSaveStates()
	{
	}
}
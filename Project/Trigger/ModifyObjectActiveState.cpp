#include "ModifyObjectActiveState.hpp"

#include <object/InstanceHandler.hpp>
#include <module/SaveFile.hpp>

namespace Trigger
{
	void ModifyObjectActiveState::executeInternal()
	{
		if (of::engine::GetModule<of::object::InstanceHandler>().exists(gameObjectToModify))
		{
			of::engine::GetModule<of::object::InstanceHandler>().getObject(gameObjectToModify)->toggleObjectState(objectState);
		}

		//of::engine::GetModule<of::module::SaveFile>().setObjectState(gameObjectToModify, objectState);

	}
	std::unique_ptr<of::trigger::Trigger> ModifyObjectActiveState::clone() const
	{
		return std::make_unique<ModifyObjectActiveState>(*this);
	}
}
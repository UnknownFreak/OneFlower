#include "ModifyObjectActiveState.hpp"

#include <module/ModuleManager.hpp>
#include <module/ObjectInstanceHandler.hpp>
#include <module/SaveFile.hpp>

namespace Trigger
{
	void ModifyObjectActiveState::executeInternal()
	{
		if (of::engine::GetModule<of::module::ObjectInstanceHandler>().exists(gameObjectToModify))
		{
			of::engine::GetModule<of::module::ObjectInstanceHandler>().getObject(gameObjectToModify)->toggleObjectState(objectState);
		}

		//of::engine::GetModule<of::module::SaveFile>().setObjectState(gameObjectToModify, objectState);

	}
	std::unique_ptr<of::resource::trigger::Trigger> ModifyObjectActiveState::clone() const
	{
		return std::make_unique<ModifyObjectActiveState>(*this);
	}
}
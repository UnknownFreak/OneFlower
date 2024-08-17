#include "ModifyObjectActiveState.hpp"

#include <object/InstanceHandler.hpp>
#include <file/SaveFile.hpp>

namespace Trigger
{
	void ModifyObjectActiveState::executeInternal()
	{
		auto& handler = of::object::get();
		if (handler.exists(gameObjectToModify))
		{
			handler.getObject(gameObjectToModify)->toggleObjectState(objectState);
		}

		//of::engine::GetModule<of::module::SaveFile>().setObjectState(gameObjectToModify, objectState);

	}
	std::unique_ptr<of::trigger::Trigger> ModifyObjectActiveState::clone() const
	{
		return std::make_unique<ModifyObjectActiveState>(*this);
	}
}
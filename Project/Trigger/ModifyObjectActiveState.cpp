#include "ModifyObjectActiveState.hpp"

#include <Object/ObjectInstanceHandler.hpp>
#include <File/SaveFile.hpp>

namespace Trigger
{
	void ModifyObjectActiveState::executeInternal()
	{
		if (of::engine::GetModule<EngineModule::ObjectInstanceHandler>().exists(gameObjectToModify))
		{
			of::engine::GetModule<EngineModule::ObjectInstanceHandler>().getObject(gameObjectToModify)->toggleObjectState(objectState);
		}
		of::engine::GetModule<File::SaveFile>().setObjectState(gameObjectToModify, objectState);

	}
	std::unique_ptr<Trigger> ModifyObjectActiveState::clone() const
	{
		return std::make_unique<ModifyObjectActiveState>(*this);
	}
}